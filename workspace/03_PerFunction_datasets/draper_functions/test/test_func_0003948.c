MD5_new(PyObject *self, PyObject *args)
{
    md5object *md5p;
    Py_buffer view = { 0 };
    Py_ssize_t n;
    unsigned char *buf;

    if (!PyArg_ParseTuple(args, "|s*:new", &view))
        return NULL;

    if ((md5p = newmd5object()) == NULL) {
        PyBuffer_Release(&view);
        return NULL;
    }

    n = view.len;
    buf = (unsigned char *) view.buf;
    while (n > 0) {
        Py_ssize_t nbytes;
        if (n > INT_MAX)
            nbytes = INT_MAX;
        else
            nbytes = n;
        md5_append(&md5p->md5, buf,
                   Py_SAFE_DOWNCAST(nbytes, Py_ssize_t, unsigned int));
        buf += nbytes;
        n -= nbytes;
    }
    PyBuffer_Release(&view);

    return (PyObject *)md5p;
}
