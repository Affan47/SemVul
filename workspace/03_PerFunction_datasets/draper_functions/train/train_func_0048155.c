PyArg_UnpackTuple(PyObject *args, const char *name, Py_ssize_t min, Py_ssize_t max, ...)
{
    Py_ssize_t i, l;
    PyObject **o;
    va_list vargs;

#ifdef HAVE_STDARG_PROTOTYPES
    va_start(vargs, max);
#else
    va_start(vargs);
#endif

    assert(min >= 0);
    assert(min <= max);
    if (!PyTuple_Check(args)) {
        va_end(vargs);
        PyErr_SetString(PyExc_SystemError,
            "PyArg_UnpackTuple() argument list is not a tuple");
        return 0;
    }
    l = PyTuple_GET_SIZE(args);
    if (l < min) {
        if (name != NULL)
            PyErr_Format(
                PyExc_TypeError,
                "%s expected %s%zd arguments, got %zd",
                name, (min == max ? "" : "at least "), min, l);
        else
            PyErr_Format(
                PyExc_TypeError,
                "unpacked tuple should have %s%zd elements,"
                " but has %zd",
                (min == max ? "" : "at least "), min, l);
        va_end(vargs);
        return 0;
    }
    if (l > max) {
        if (name != NULL)
            PyErr_Format(
                PyExc_TypeError,
                "%s expected %s%zd arguments, got %zd",
                name, (min == max ? "" : "at most "), max, l);
        else
            PyErr_Format(
                PyExc_TypeError,
                "unpacked tuple should have %s%zd elements,"
                " but has %zd",
                (min == max ? "" : "at most "), max, l);
        va_end(vargs);
        return 0;
    }
    for (i = 0; i < l; i++) {
        o = va_arg(vargs, PyObject **);
        *o = PyTuple_GET_ITEM(args, i);
    }
    va_end(vargs);
    return 1;
}
