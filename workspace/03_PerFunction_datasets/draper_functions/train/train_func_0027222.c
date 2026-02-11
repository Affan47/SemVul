get_format(PyObject *format)
{
    PyObject *tmp;
    char *fmt;

    tmp = PyUnicode_AsASCIIString(format);
    if (tmp == NULL)
        return NULL;
    fmt = PyMem_Malloc(PyBytes_GET_SIZE(tmp)+1);
    if (fmt == NULL) {
        PyErr_NoMemory();
        Py_DECREF(tmp);
        return NULL;
    }
    strcpy(fmt, PyBytes_AS_STRING(tmp));
    Py_DECREF(tmp);

    return fmt;
}
