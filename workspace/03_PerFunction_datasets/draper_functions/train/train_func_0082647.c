PyFloat_FromString(PyObject *v)
{
    const char *s, *last, *end;
    double x;
    PyObject *s_buffer = NULL;
    Py_ssize_t len;
    Py_buffer view = {NULL, NULL};
    PyObject *result = NULL;

    if (PyUnicode_Check(v)) {
        s_buffer = _PyUnicode_TransformDecimalAndSpaceToASCII(v);
        if (s_buffer == NULL)
            return NULL;
        s = PyUnicode_AsUTF8AndSize(s_buffer, &len);
        if (s == NULL) {
            Py_DECREF(s_buffer);
            return NULL;
        }
    }
    else if (PyObject_GetBuffer(v, &view, PyBUF_SIMPLE) == 0) {
        s = (const char *)view.buf;
        len = view.len;
    }
    else {
        PyErr_Format(PyExc_TypeError,
            "float() argument must be a string or a number, not '%.200s'",
            Py_TYPE(v)->tp_name);
        return NULL;
    }
    last = s + len;

    while (s < last && Py_ISSPACE(*s))
        s++;
    while (s < last - 1 && Py_ISSPACE(last[-1]))
        last--;


    x = PyOS_string_to_double(s, (char **)&end, NULL);
    if (end != last) {
        PyErr_Format(PyExc_ValueError,
                     "could not convert string to float: "
                     "%R", v);
        result = NULL;
    }
    else if (x == -1.0 && PyErr_Occurred())
        result = NULL;
    else
        result = PyFloat_FromDouble(x);

    PyBuffer_Release(&view);
    Py_XDECREF(s_buffer);
    return result;
}
