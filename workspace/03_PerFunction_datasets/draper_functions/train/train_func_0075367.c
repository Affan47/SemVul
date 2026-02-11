crm_time_new(const char *date_time)
{
    time_t tm_now;
    crm_time_t *dt = NULL;

    tzset();
    if (date_time == NULL) {
        tm_now = time(NULL);
        dt = calloc(1, sizeof(crm_time_t));
        crm_time_set_timet(dt, &tm_now);
    } else {
        dt = parse_date(date_time);
    }
    return dt;
}
