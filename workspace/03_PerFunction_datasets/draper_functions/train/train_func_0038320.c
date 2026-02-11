Stream_init(StreamObject *self, PyObject *args, PyObject *kwds)
{
    PyObject *filelike = NULL;
    apr_size_t blksize = HUGE_STRING_LEN;

    static char *kwlist[] = { "filelike", "blksize", NULL };

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O|l:FileWrapper", kwlist,
                                     &filelike, &blksize)) {
        return -1;
    }

    if (filelike) {
        PyObject *tmp = NULL;

        tmp = self->filelike;
        Py_INCREF(filelike);
        self->filelike = filelike;
        Py_XDECREF(tmp);
    }

    self->blksize = blksize;

    return 0;
}
