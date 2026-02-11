builtin_ord(PyObject *self, PyObject* obj)
{
    long ord;
    Py_ssize_t size;

    if (PyString_Check(obj)) {
        size = PyString_GET_SIZE(obj);
        if (size == 1) {
            ord = (long)((unsigned char)*PyString_AS_STRING(obj));
            return PyInt_FromLong(ord);
        }
    } else if (PyByteArray_Check(obj)) {
        size = PyByteArray_GET_SIZE(obj);
        if (size == 1) {
            ord = (long)((unsigned char)*PyByteArray_AS_STRING(obj));
            return PyInt_FromLong(ord);
        }

#ifdef Py_USING_UNICODE
    } else if (PyUnicode_Check(obj)) {
        size = PyUnicode_GET_SIZE(obj);
        if (size == 1) {
            ord = (long)*PyUnicode_AS_UNICODE(obj);
            return PyInt_FromLong(ord);
        }
#endif
    } else {
        PyErr_Format(PyExc_TypeError,
                     "ord() expected string of length 1, but " \
                     "%.200s found", obj->ob_type->tp_name);
        return NULL;
    }

    PyErr_Format(PyExc_TypeError,
                 "ord() expected a character, "
                 "but string of length %zd found",
                 size);
    return NULL;
}
