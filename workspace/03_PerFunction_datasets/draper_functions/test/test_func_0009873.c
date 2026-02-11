datetime_set_month(DateTime * dt, int month)
{
    int stat;

    stat = datetime_check_month(dt, month);
    if (stat == 0) {
	dt->month = month;
	if (datetime_is_absolute(dt))
	    dt->day = 0;
    }

    return stat;
}
