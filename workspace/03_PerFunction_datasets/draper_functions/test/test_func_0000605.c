bufferedrwpair_isatty(rwpair *self, PyObject *args)
{
    PyObject *ret = _forward_call(self->writer, &PyId_isatty, args);

    if (ret != Py_False) {

        return ret;
    }
    Py_DECREF(ret);

    return _forward_call(self->reader, &PyId_isatty, args);
}
