charset_convert(Octstr* string, char* charset_from, char* charset_to)
{
#if HAVE_ICONV
    char *from_buf, *to_buf, *pointer;
    size_t inbytesleft, outbytesleft, ret;
    iconv_t cd;

    if (!charset_from || !charset_to || !string)
        return -1;

    if (octstr_len(string) < 1)
        return 0;

    cd = iconv_open(charset_to, charset_from);

    if (cd == (iconv_t)(-1)) {

        error(0,"Failed to convert string from <%s> to <%s> - probably broken type names.",
              charset_from, charset_to);
        return -1;
    }

    from_buf = octstr_get_cstr(string);
    inbytesleft = octstr_len(string);

    outbytesleft = inbytesleft * 4;
    pointer = to_buf = gw_malloc(outbytesleft);

    do {
        ret = iconv(cd, (ICONV_CONST char**) &from_buf, &inbytesleft, &pointer, &outbytesleft);
        if(ret == -1) {
            long tmp;

            switch(errno) {
            case E2BIG:
                debug("charset", 0, "outbuf to small, realloc.");
                tmp = pointer - to_buf;
                to_buf = gw_realloc(to_buf, tmp + inbytesleft * 4);
                outbytesleft += inbytesleft * 4;
                pointer = to_buf + tmp;
                ret = 0;
                break;
            case EILSEQ:
            case EINVAL:
                warning(0, "Invalid/Incomplete multibyte sequence at position %d, skeep it.",
                        (int)(from_buf - octstr_get_cstr(string)));

                if (outbytesleft == 0) {

                    tmp = pointer - to_buf;
                    to_buf = gw_realloc(to_buf, tmp + inbytesleft * 4);
                    outbytesleft += inbytesleft * 4;
                    pointer = to_buf + tmp;
                }
                pointer[0] = from_buf[0];
                pointer++;
                from_buf++;
                inbytesleft--;
                outbytesleft--;
                ret = 0;
                break;
            }
        }
    } while(inbytesleft && ret == 0);

    iconv_close(cd);

    if (ret != -1) {

        octstr_truncate(string, 0);
        octstr_append_data(string, to_buf, pointer - to_buf);
        if (ret)
            debug("charset", 0, "charset_convert did %ld non-reversible conversions", (long) ret);
        ret = 0;
    } else
        error(errno,"Failed to convert string from <%s> to <%s>.", charset_from, charset_to);

    if (errno == EILSEQ) {
        debug("charset_convert", 0, "Found an invalid multibyte sequence at position <%d>",
              (int)(from_buf - octstr_get_cstr(string)));
    }
    gw_free(to_buf);
    return ret;
#endif

    return -1;
}
