jk_ajp_get_cping_mode(const char *m, int def)
{
    int mv = def;
    if (!m)
        return mv;
    while (*m != '\0') {
        if (*m == 'C' || *m == 'c')
            mv |= AJP_CPING_CONNECT;
        if (*m == 'P' || *m == 'p')
            mv |= AJP_CPING_PREPOST;
        if (*m == 'I' || *m == 'i')
            mv |= AJP_CPING_INTERVAL;
        if (*m == 'A' || *m == 'a') {
            mv = AJP_CPING_CONNECT | AJP_CPING_PREPOST | AJP_CPING_INTERVAL;
            break;
        }
        m++;
    }
    return mv;
}
