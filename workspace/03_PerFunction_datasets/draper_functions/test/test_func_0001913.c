print_system(void)
{
    char *buf;

    BUFFER_CLEAR(buf);

    buf += sprintf(buf, "%s", FCV_SYSTEM_TABLE_HEADER);
    NEW_LINE(buf);
    buf += sprintf(buf, "file <%s>;", RFM_System->file_name);
    NEW_LINE(buf);
    if ((RFM_System->language > RFM_LANG_UNDEFINED) &&
        (RFM_System->language < RFM_LANG_MAX_NUM)) {
        buf += sprintf(buf, "language <%s>;",
                       RFM_LangString[RFM_System->language]);
    } else {
        buf += sprintf(buf, "language <%s>;",
                       RFM_LangString[RFM_LANG_UNDEFINED]);
    }
    NEW_LINE(buf);

    NEW_LINE(buf);
}
