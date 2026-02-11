DateCalc_delta_ymd(Z_int *year1, Z_int *month1, Z_int *day1,
                           Z_int  year2, Z_int  month2, Z_int  day2)
{
    if (DateCalc_check_date(*year1,*month1,*day1) and
        DateCalc_check_date(year2,month2,day2))
    {
        *day1   = day2   - *day1;
        *month1 = month2 - *month1;
        *year1  = year2  - *year1;
        return(true);
    }
    return(false);
}
