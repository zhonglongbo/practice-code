
#include"practice.h"

bool IsLeapYear(int year)
{
	if((year % 4 == 0 && year % 100 != 0)
		|| (year % 400 == 0))
		return true;
	return false;
}

int GetMonthDay(int year, int month)
{
	assert(month>0 && month<13);
	int days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if(month == 2 && IsLeapYear(year))
		days[2] = 29;
	return days[month];
}

Date::Date(int year, int month, int day)
{
	assert(month<13 && month>0 && day>0 && day < GetMonthDay(year, month));
	_year = year;
	_month = month;
	_day = day;
}

void Date::Show()
{
	std::cout << _year << "-" << _month << "-" << _day << std::endl;
}

bool Date::operator==(Date& d)
{
	return (_year == d._year
		&&_month == d._month
		&&_day == d._day);
}

bool Date::operator!=(Date& d)
{
	return !(*this == d);
}

bool Date::operator<(Date& d)
{
	if(_year<d._year
		|| (_year == d._year && _month<d._month)
		|| (_year == d._year && _month == d._month && _day<d._day))
		return true;
	return false;
}

bool Date::operator>(Date& d)
{
	return !(*this<d);
}

bool Date::operator<=(Date& d)
{
	return (*this<d) || (*this == d);
}

bool Date::operator>=(Date& d)
{
	return !(*this < d);
}

Date& Date::operator=(const Date& d)
{
	if(this != &d)
	{
		(*this)._year = d._year;
		(*this)._month = d._month;
		(*this)._day = d._day;
	}
	return *this;
}

Date Date::operator+(int day)
{
	if(day<0)
	{
		day = -day;
		return *this-day;
	}
	Date ret = *this;
	ret._day += day;
	while(ret._day>GetMonthDay(ret._year, ret._month))
	{
		ret._day -= GetMonthDay(ret._year, ret._month);
		ret._month++;
		if(ret._month == 13)
		{
			ret._year++;
			ret._month = 1;
		}
	}
	return ret;
}

Date Date::operator-(int day)
{
	if(day<0)
	{
		day = -day;
		return *this + day;
	}
	Date ret = *this;
	ret._day -= day;
	if(ret._day>0)
		return ret;
	while(ret._day <= 0)
	{
		ret._month--;
		if(ret._month == 0)
		{
			ret._year--;
			ret._month = 12;
		}
		ret._day += GetMonthDay(ret._year, ret._month);
	}
	return ret;
}
Date& Date::operator+=(int day)
{
	return (*this = (*this + day));
}

Date& Date::operator-=(int day)
{
	return (*this = (*this - day));
}

Date& Date::operator++()//ǰ��
{
	return *this = *this + 1;
}

Date Date::operator++(int)//����
{
	Date ret(*this);
	*this = *this + 1;
	return ret;
}

Date& Date::operator--()//ǰ��
{
	return *this = *this - 1;
}

Date Date::operator--(int)//����
{
	Date ret(*this);
	*this = *this - 1;
	return ret;
}

int Date::operator-(Date& d)
{
	Date Max(*this);
	Date Min(d);
	
	if(*this < d)
	{
		Max = d;
		Min = *this;
	}
	int count = 0;
	while(Max != Min)
	{
		count++;
		Min++;
	}
	return count;
}
