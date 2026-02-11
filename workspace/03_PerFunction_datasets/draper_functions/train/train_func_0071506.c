plog_dump(int level, const char *prefix, void *buf, int len)
{
    int i;
    uint8_t *p;

    p = (uint8_t *) buf;
    for (i = 0; i < len; i++)
        plog(level, "%s: %02x %c", prefix, p[i], p[i]);
}
