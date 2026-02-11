plog_func(int level, const char *func, const char *msg)
{
    if (LogFlags & DNS_LOG_FLAG_TRACE)
        plog(level, "%s: %s", func, msg);
}
