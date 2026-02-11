_Py_bytes_isalpha(const char *cptr, Py_ssize_t len)
{
    register const unsigned char *p
        = (unsigned char *) cptr;
    register const unsigned char *e;


    if (len == 1 && Py_ISALPHA(*p))
        Py_RETURN_TRUE;


    if (len == 0)
        Py_RETURN_FALSE;

    e = p + len;
    for (; p < e; p++) {
        if (!Py_ISALPHA(*p))
            Py_RETURN_FALSE;
    }
    Py_RETURN_TRUE;
}
