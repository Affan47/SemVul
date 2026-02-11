bytearray_reduce(PyByteArrayObject *self)
{
    PyObject *latin1, *dict;
    if (self->ob_bytes)
#ifdef Py_USING_UNICODE
        latin1 = PyUnicode_DecodeLatin1(self->ob_bytes,
                                        Py_SIZE(self), NULL);
#else
        latin1 = PyString_FromStringAndSize(self->ob_bytes, Py_SIZE(self));
#endif
    else
#ifdef Py_USING_UNICODE
        latin1 = PyUnicode_FromString("");
#else
        latin1 = PyString_FromString("");
#endif

    dict = PyObject_GetAttrString((PyObject *)self, "__dict__");
    if (dict == NULL) {
        PyErr_Clear();
        dict = Py_None;
        Py_INCREF(dict);
    }

    return Py_BuildValue("(O(Ns)N)", Py_TYPE(self), latin1, "latin-1", dict);
}
