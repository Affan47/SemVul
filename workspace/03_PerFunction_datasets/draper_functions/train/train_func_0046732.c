s_unpack(PyObject *self, PyObject *input)
{
    Py_buffer vbuf;
    PyObject *result;
    PyStructObject *soself = (PyStructObject *)self;

    assert(PyStruct_Check(self));
    assert(soself->s_codes != NULL);
    if (PyObject_GetBuffer(input, &vbuf, PyBUF_SIMPLE) < 0)
        return NULL;
    if (vbuf.len != soself->s_size) {
        PyErr_Format(StructError,
                     "unpack requires a bytes object of length %zd",
                     soself->s_size);
        PyBuffer_Release(&vbuf);
        return NULL;
    }
    result = s_unpack_internal(soself, vbuf.buf);
    PyBuffer_Release(&vbuf);
    return result;
}
