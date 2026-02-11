netsnmp_dateandtime_set_buf_from_vars(u_char *buf, size_t *bufsize,
                                      u_short year, u_char month, u_char day,
                                      u_char hour, u_char minutes,
                                      u_char seconds, u_char deci_seconds,
                                      int utc_offset_direction,
                                      u_char utc_offset_hours,
                                      u_char utc_offset_minutes)
{
    u_short tmp_year = htons(year);


    if(utc_offset_direction) {
        if(*bufsize < 11)
            return SNMPERR_RANGE;


        buf[8] = (utc_offset_direction < 0) ? '-' : '+';
        buf[9] = utc_offset_hours;
        buf[10] = utc_offset_minutes;
        *bufsize = 11;
    }
    else if(*bufsize < 8)
        return SNMPERR_RANGE;
    else
        *bufsize = 8;


    memcpy(buf, &tmp_year, sizeof(tmp_year));
    buf[2] = month;
    buf[3] = day;
    buf[4] = hour;
    buf[5] = minutes;
    buf[6] = seconds;
    buf[7] = deci_seconds;

    return SNMPERR_SUCCESS;
}
