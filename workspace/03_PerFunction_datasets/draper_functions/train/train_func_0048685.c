float_getformat(PyTypeObject *v, PyObject* arg)
{
    char* s;
    float_format_type r;

    if (!PyString_Check(arg)) {
        PyErr_Format(PyExc_TypeError,
         "__getformat__() argument must be string, not %.500s",
                         Py_TYPE(arg)->tp_name);
        return NULL;
    }
    s = PyString_AS_STRING(arg);
    if (strcmp(s, "double") == 0) {
        r = double_format;
    }
    else if (strcmp(s, "float") == 0) {
        r = float_format;
    }
    else {
        PyErr_SetString(PyExc_ValueError,
                        "__getformat__() argument 1 must be "
                        "'double' or 'float'");
        return NULL;
    }

    switch (r) {
    case unknown_format:
        return PyString_FromString("unknown");
    case ieee_little_endian_format:
        return PyString_FromString("IEEE, little-endian");
    case ieee_big_endian_format:
        return PyString_FromString("IEEE, big-endian");
    default:
        Py_FatalError("insane float_format or double_format");
        return NULL;
    }
}
