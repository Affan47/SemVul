xmlparse_ParseFile(xmlparseobject *self, PyObject *f)
{
    int rv = 1;
    PyObject *readmethod = NULL;
    _Py_IDENTIFIER(read);

    readmethod = _PyObject_GetAttrId(f, &PyId_read);
    if (readmethod == NULL) {
        PyErr_SetString(PyExc_TypeError,
                        "argument must have 'read' attribute");
        return NULL;
    }
    for (;;) {
        int bytes_read;
        void *buf = XML_GetBuffer(self->itself, BUF_SIZE);
        if (buf == NULL) {
            Py_XDECREF(readmethod);
            return get_parse_result(self, 0);
        }

        bytes_read = readinst(buf, BUF_SIZE, readmethod);
        if (bytes_read < 0) {
            Py_DECREF(readmethod);
            return NULL;
        }
        rv = XML_ParseBuffer(self->itself, bytes_read, bytes_read == 0);
        if (PyErr_Occurred()) {
            Py_XDECREF(readmethod);
            return NULL;
        }

        if (!rv || bytes_read == 0)
            break;
    }
    Py_XDECREF(readmethod);
    return get_parse_result(self, rv);
}
