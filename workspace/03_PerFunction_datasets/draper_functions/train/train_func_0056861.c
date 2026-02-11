bytearray_rindex(PyByteArrayObject *self, PyObject *args)
{
    Py_ssize_t result = bytearray_find_internal(self, args, -1);
    if (result == -2)
        return NULL;
    if (result == -1) {
        PyErr_SetString(PyExc_ValueError,
                        "subsection not found");
        return NULL;
    }
    return PyInt_FromSsize_t(result);
}
