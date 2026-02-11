wsgi_validate_header_value(PyObject *value)
{
    const char *s;

    if (!PyBytes_Check(value)) {
        PyErr_Format(PyExc_TypeError, "expected byte string object for "
                     "header value, value of type %.200s found",
                     value->ob_type->tp_name);
        return 0;
    }

    s = PyBytes_AsString(value);

    while (*s) {
        if (*s == '\r' || *s == '\n') {
            PyErr_SetString(PyExc_ValueError, "carriage return/line "
                            "feed character present in header value");
            return 0;
        }
        s++;
    }

    return 1;
}
