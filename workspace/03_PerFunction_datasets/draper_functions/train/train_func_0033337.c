strbuf_append_fmt_retry(strbuf_t *s, const char *fmt, ...)
{
    va_list arg;
    int fmt_len, try;
    int empty_len;


    for (try = 0; ; try++) {
        va_start(arg, fmt);


        empty_len = strbuf_empty_length(s);

        fmt_len = vsnprintf(s->buf + s->length, empty_len + 1, fmt, arg);
        va_end(arg);

        if (fmt_len <= empty_len)
            break;
        if (try > 0)
            luaL_error(s->lua, "BUG: length of formatted string changed");

        strbuf_resize(s, s->length + fmt_len);
    }

    s->length += fmt_len;
}
