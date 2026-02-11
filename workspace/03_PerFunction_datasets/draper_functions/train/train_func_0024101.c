stringio_seekable(stringio *self, PyObject *args)
{
    CHECK_INITIALIZED(self);
    CHECK_CLOSED(self);
    Py_RETURN_TRUE;
}
