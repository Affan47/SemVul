crm_time_parse_offset(const char *offset_str)
{
    int offset = 0;

    tzset();
    if (offset_str == NULL) {
#if defined(HAVE_STRUCT_TM_TM_GMTOFF)
        time_t now = time(NULL);
        struct tm *now_tm = localtime(&now);
#endif
        int h_offset = GMTOFF(now_tm) / (3600);
        int m_offset = (GMTOFF(now_tm) - (3600 * h_offset)) / (60);

        if (h_offset < 0 && m_offset < 0) {
            m_offset = 0 - m_offset;
        }
        offset += (60 * 60 * h_offset);
        offset += (60 * m_offset);

    } else if (offset_str[0] == 'Z') {

    } else if (offset_str[0] == '+' || offset_str[0] == '-' || isdigit((int)offset_str[0])) {
        gboolean negate = FALSE;

        if (offset_str[0] == '-') {
            negate = TRUE;
            offset_str++;
        }
        offset = crm_time_parse_sec(offset_str);
        if (negate) {
            offset = 0 - offset;
        }
    }
    return offset;
}
