format(double bytes)
{
    static char buf[256];

    if (bytes >= 1024 * 1024 * 1024)
        snprintf(buf, sizeof(buf), "%.2f GiB", (bytes / 1024 / 1024 / 1024));
    else if (bytes >= 1024 * 1024)
        snprintf(buf, sizeof(buf), "%.2f MiB", (bytes / 1024 / 1024));
    else if (bytes >= 1024)
        snprintf(buf, sizeof(buf), "%.2f KiB", (bytes / 1024));
    else
        snprintf(buf, sizeof(buf), "%.0f bytes", bytes);

    return buf;
}
