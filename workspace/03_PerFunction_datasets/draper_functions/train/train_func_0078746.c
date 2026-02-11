_check(lms_charset_conv_t *lcc, const char *istr, unsigned int ilen, char *ostr, unsigned int olen)
{
    char *inbuf, *outbuf;
    size_t r, inlen, outlen;

    if (lcc->check == (iconv_t)-1)
        return -1;

    inbuf = (char *)istr;
    inlen = ilen;
    outbuf = ostr;
    outlen = olen;

    iconv(lcc->check, NULL, NULL, NULL, NULL);
    r = iconv(lcc->check, &inbuf, &inlen, &outbuf, &outlen);
    if (r == (size_t)-1)
        return -1;
    else
        return 0;
}
