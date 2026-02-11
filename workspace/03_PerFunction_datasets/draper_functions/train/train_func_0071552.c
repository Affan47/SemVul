print_buffer(const unsigned char *buf, unsigned int len)
{
    unsigned  i = 0;
    if (len <= 0)
        return;

    for (i = 0; i < len; i++)
        pkiDebug("%02x ", buf[i]);
    pkiDebug("\n");
}
