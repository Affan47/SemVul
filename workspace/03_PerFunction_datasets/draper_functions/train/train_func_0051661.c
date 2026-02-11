PyBuffer_FromObject(PyObject *base, Py_ssize_t offset, Py_ssize_t size)
{
    PyBufferProcs *pb = base->ob_type->tp_as_buffer;

    if ( pb == NULL ||
         pb->bf_getreadbuffer == NULL ||
         pb->bf_getsegcount == NULL )
    {
        PyErr_SetString(PyExc_TypeError, "buffer object expected");
        return NULL;
    }

    return buffer_from_object(base, size, offset, 1);
}
