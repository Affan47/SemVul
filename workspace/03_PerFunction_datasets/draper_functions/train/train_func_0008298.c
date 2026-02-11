parse_iso88591_to_emi(char *from, char *to,
        int length, int alt_charset)
{
    char buf[10];
    unsigned char tmpchar;
    char *ptr;

    if (!from || !to || length <= 0)
        return -1;

    *to = '\0';

    debug("bb.sms.emi", 0, "emi parsing <%s> to emi, length %d", from, length);

    for (ptr = from; length > 0; ptr++, length--) {
        tmpchar = char_iso_to_sms(*ptr, alt_charset);
        sprintf(buf, "%02X", tmpchar);
        strncat(to, buf, 2);
    }
    return 0;
}
