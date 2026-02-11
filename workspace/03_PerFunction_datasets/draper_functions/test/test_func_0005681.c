add_datetime_timedelta(PyDateTime_DateTime *date, PyDateTime_Delta *delta,
                       int factor)
{


    int year = GET_YEAR(date);
    int month = GET_MONTH(date);
    int day = GET_DAY(date) + GET_TD_DAYS(delta) * factor;
    int hour = DATE_GET_HOUR(date);
    int minute = DATE_GET_MINUTE(date);
    int second = DATE_GET_SECOND(date) + GET_TD_SECONDS(delta) * factor;
    int microsecond = DATE_GET_MICROSECOND(date) +
                      GET_TD_MICROSECONDS(delta) * factor;

    assert(factor == 1 || factor == -1);
    if (normalize_datetime(&year, &month, &day,
                           &hour, &minute, &second, &microsecond) < 0)
        return NULL;
    else
        return new_datetime(year, month, day,
                            hour, minute, second, microsecond,
                            HASTZINFO(date) ? date->tzinfo : Py_None);
}
