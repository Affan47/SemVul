bytes_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    PyObject *x = NULL;
    const char *encoding = NULL;
    const char *errors = NULL;
    PyObject *new = NULL;
    Py_ssize_t size;
    static char *kwlist[] = {"source", "encoding", "errors", 0};

    if (type != &PyBytes_Type)
        return str_subtype_new(type, args, kwds);
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|Oss:bytes", kwlist, &x,
                                     &encoding, &errors))
        return NULL;
    if (x == NULL) {
        if (encoding != NULL || errors != NULL) {
            PyErr_SetString(PyExc_TypeError,
                            "encoding or errors without sequence "
                            "argument");
            return NULL;
        }
        return PyBytes_FromString("");
    }

    if (PyUnicode_Check(x)) {

        if (encoding == NULL) {
            PyErr_SetString(PyExc_TypeError,
                            "string argument without an encoding");
            return NULL;
        }
        new = PyUnicode_AsEncodedString(x, encoding, errors);
        if (new == NULL)
            return NULL;
        assert(PyBytes_Check(new));
        return new;
    }

    size = PyNumber_AsSsize_t(x, PyExc_OverflowError);
    if (size == -1 && PyErr_Occurred()) {
        if (PyErr_ExceptionMatches(PyExc_OverflowError))
            return NULL;
        PyErr_Clear();
    }
    else if (size < 0) {
        PyErr_SetString(PyExc_ValueError, "negative count");
        return NULL;
    }
    else {
        new = PyBytes_FromStringAndSize(NULL, size);
        if (new == NULL) {
            return NULL;
        }
        if (size > 0) {
            memset(((PyBytesObject*)new)->ob_sval, 0, size);
        }
        return new;
    }


    if (encoding != NULL || errors != NULL) {
        PyErr_SetString(PyExc_TypeError,
            "encoding or errors without a string argument");
        return NULL;
    }
    return PyObject_Bytes(x);
}
