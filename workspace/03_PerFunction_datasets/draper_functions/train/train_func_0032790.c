_cx_string_vsprintf(cx_string *string, const cxchar *format, va_list args)
{

    cxint n;
    cxchar *tmp = NULL;

    n = cx_vasprintf(&tmp, format, args);

    if (tmp) {
        if (string->data != NULL) {
            cx_free(string->data);
        }

        string->data = tmp;
        string->sz = (cxsize) strlen(tmp);
    }

    return n;

}
