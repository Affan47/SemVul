format_sec(char *buf, size_t len, unsigned long csec)
{
    long sec, min, hour, day;

    day = csec / 100 / 3600 / 24;
    csec -= day * 100 * 3600 * 24;
    hour = csec / 100 / 3600;
    csec -= hour * 100 * 3600;
    min = csec / 100 / 60;
    csec -= min * 100 * 60;
    sec = csec / 100;
    csec -= sec * 100;

    if (day)
        snprintf(buf, len, "%ldd%02ld:%02ld:%02ld", day, hour, min, sec);
    else if (hour)
        snprintf(buf, len, "%ld:%02ld:%02ld.%02lu", hour, min, sec, csec);
    else if (min)
        snprintf(buf, len, "%ld:%02ld.%02lu", min, sec, csec);
    else
        snprintf(buf, len, "%ld.%02lu", sec, csec);
    return buf;
}
