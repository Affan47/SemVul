get_shape0(Py_buffer *buf)
{
    if (buf->shape != NULL)
        return buf->shape[0];
    if (buf->ndim == 0)
        return 1;
    PyErr_SetString(PyExc_TypeError,
        "exported buffer does not have any shape information associated "
        "to it");
    return -1;
}
