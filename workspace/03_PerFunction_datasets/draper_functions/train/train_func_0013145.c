gSendStrN(const char *buf, int len)
{
    if (buf)
        gSendNStr(buf, strnlen(buf, len));
    else
        gSendStr(buf);
}
