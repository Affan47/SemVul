icaltime_days_in_month(const int month, const int year)
{

    int days = _days_in_month[month];


    if ((month < 1) || (month > 12)) {
	return 30;
    }

    if( month == 2){
	days += icaltime_is_leap_year(year);
    }

    return days;
}
