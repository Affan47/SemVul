date_parse_iso (struct universaltime *ut, Octstr *os)
{
    int n = 0;
    char *p, *q;


    ut->month = 0;
    ut->day = 1;
    ut->hour = 0;
    ut->minute = 0;
    ut->second = 0;

    p = octstr_get_cstr(os);
    q = p + ((n = octstr_search_char(os, 'T', 0)) >= 0 ? n : octstr_len(os));
    if (sscanf(p, "%4ld%n", &ut->year, &n) < 1)
        return -1;
    p += n;

    if (ut->year < 70)
        ut->year += 2000;
    else if (ut->year < 100)
	ut->year += 1900;

    while (p < q && !gw_isdigit(*p))
	p++;
    if (sscanf(p, "%2ld%n", &ut->month, &n) < 1)
	return 0;
    p += n;


    if (ut->month > 0)
	ut->month--;

    while (p < q && !gw_isdigit(*p))
        p++;
    if (sscanf(p, "%2ld%n", &ut->day, &n) < 1)
	return 0;
    p += n;

    if (*q == 'T')
	p = q+1;
    else
        return 0;

    while (*p && !gw_isdigit(*p))
	p++;
    if (sscanf(p, "%2ld%n", &ut->hour, &n) < 1)
	return 0;
    p += n;

    while (*p && !gw_isdigit(*p))
	p++;
    if (sscanf(p, "%2ld%n", &ut->minute, &n) < 1)
	return 0;
    p += n;

    while (*p && !gw_isdigit(*p))
	p++;
    if (sscanf(p, "%2ld%n", &ut->second, &n) < 1)
	return 0;
     p += n;

    return 0;
}
