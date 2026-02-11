PyLong_FromUnicodeObject(PyObject *u, int base)
{
    PyObject *result;
    PyObject *asciidig;
    char *buffer, *end;
    Py_ssize_t buflen;

    asciidig = _PyUnicode_TransformDecimalAndSpaceToASCII(u);
    if (asciidig == NULL)
        return NULL;
    buffer = PyUnicode_AsUTF8AndSize(asciidig, &buflen);
    if (buffer == NULL) {
        Py_DECREF(asciidig);
        return NULL;
    }
    result = PyLong_FromString(buffer, &end, base);
    if (result != NULL && end != buffer + buflen) {
        PyErr_SetString(PyExc_ValueError,
                        "null byte in argument for int()");
        Py_DECREF(result);
        result = NULL;
    }
    Py_DECREF(asciidig);
    return result;
}
