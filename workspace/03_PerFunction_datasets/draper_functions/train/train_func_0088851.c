u8_escape(char *buf, size_t sz, const char *src, size_t *pi, size_t end,
                 int escape_quotes, int ascii)
{
    size_t i = *pi, i0;
    uint32_t ch;
    char *start = buf;
    char *blim = start + sz-11;
    assert(sz > 11);

    while (i<end && buf<blim) {

        if (escape_quotes && src[i] == '"') {
            buf += buf_put2c(buf, "\\\"");
            i++;
        }
        else if (src[i] == '\\') {
            buf += buf_put2c(buf, "\\\\");
            i++;
        }
        else {
            i0 = i;
            ch = u8_nextmemchar(src, &i);
            if (ascii || !iswprint((wint_t)ch)) {
                buf += u8_escape_wchar(buf, sz - (buf-start), ch);
            }
            else {
                i = i0;
                do {
                    *buf++ = src[i++];
                } while (!isutf(src[i]));
            }
        }
    }
    *buf++ = '\0';
    *pi = i;
    return (buf-start);
}
