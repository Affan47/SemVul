getbuffer(PyObject *arg, Py_buffer *view, char **errmsg)
{
    void *buf;
    Py_ssize_t count;
    PyBufferProcs *pb = arg->ob_type->tp_as_buffer;
    if (pb == NULL) {
        *errmsg = "string or buffer";
        return -1;
    }
    if (pb->bf_getbuffer) {
        if (pb->bf_getbuffer(arg, view, 0) < 0) {
            *errmsg = "convertible to a buffer";
            return -1;
        }
        if (!PyBuffer_IsContiguous(view, 'C')) {
            *errmsg = "contiguous buffer";
            return -1;
        }
        return 0;
    }

    count = convertbuffer(arg, &buf, errmsg);
    if (count < 0) {
        *errmsg = "convertible to a buffer";
        return count;
    }
    PyBuffer_FillInfo(view, arg, buf, count, 1, 0);
    return 0;
}
