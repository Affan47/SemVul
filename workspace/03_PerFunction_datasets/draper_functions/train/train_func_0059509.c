buf_m4_define (struct Buf *buf, const char* def, const char* val)
{
    const char * fmt = "m4_define( [[%s]], [[%s]])m4_dnl\n";
    char * str;
    size_t strsz;

    val = val?val:"";
    str = (char*)flex_alloc(strsz = strlen(fmt) + strlen(def) + strlen(val) + 2);

    snprintf(str, strsz, fmt, def, val);
    buf_append(buf, &str, 1);
    return buf;
}
