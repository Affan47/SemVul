_set_char(const char *name, Py_UCS4 *target, PyObject *src, Py_UCS4 dflt)
{
    if (src == NULL)
        *target = dflt;
    else {
        *target = '\0';
        if (src != Py_None) {
            Py_ssize_t len;
            len = PyUnicode_GetLength(src);
            if (len > 1) {
                PyErr_Format(PyExc_TypeError,
                    "\"%s\" must be an 1-character string",
                    name);
                return -1;
            }
            if (len > 0)
                *target = PyUnicode_READ_CHAR(src, 0);
        }
    }
    return 0;
}
