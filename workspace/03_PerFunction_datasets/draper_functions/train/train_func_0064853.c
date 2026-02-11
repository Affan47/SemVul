bb_alog_init(const Octstr *format)
{
    gw_assert(format != NULL);

    custom_log_format = octstr_duplicate(format);
}
