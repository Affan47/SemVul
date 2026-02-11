compute_time (const GncBillTerm *term, Timespec post_date, int days)
{
    Timespec res = post_date;
    int day, month, year;

    switch (term->type)
    {
    case GNC_TERM_TYPE_DAYS:
        res.tv_sec += (SECS_PER_DAY * days);
        break;
    case GNC_TERM_TYPE_PROXIMO:
        compute_monthyear (term, post_date, &month, &year);
        day = gnc_date_get_last_mday (month, year);
        if (days < day)
            day = days;
        res = gnc_dmy2timespec (day, month, year);
        break;
    }
    return res;
}
