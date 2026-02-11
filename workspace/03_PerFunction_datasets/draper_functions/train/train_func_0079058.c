do_strip(PyObject *args, int striptype)
{
    char *s;
    Py_ssize_t len, i, j;


    if (PyString_AsStringAndSize(args, &s, &len))
        return NULL;

    i = 0;
    if (striptype != RIGHTSTRIP) {
        while (i < len && isspace(Py_CHARMASK(s[i]))) {
            i++;
        }
    }

    j = len;
    if (striptype != LEFTSTRIP) {
        do {
            j--;
        } while (j >= i && isspace(Py_CHARMASK(s[j])));
        j++;
    }

    if (i == 0 && j == len) {
        Py_INCREF(args);
        return args;
    }
    else
        return PyString_FromStringAndSize(s+i, j-i);
}
