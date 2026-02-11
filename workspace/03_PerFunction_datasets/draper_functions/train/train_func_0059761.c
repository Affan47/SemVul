PyObject_CheckReadBuffer(PyObject *obj)
{
    PyBufferProcs *pb = obj->ob_type->tp_as_buffer;
    Py_buffer view;

    if (pb == NULL ||
        pb->bf_getbuffer == NULL)
        return 0;
    if ((*pb->bf_getbuffer)(obj, &view, PyBUF_SIMPLE) == -1) {
        PyErr_Clear();
        return 0;
    }
    PyBuffer_Release(&view);
    return 1;
}
