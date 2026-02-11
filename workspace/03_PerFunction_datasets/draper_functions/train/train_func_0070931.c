SHA224_new(PyObject *self, PyObject *args, PyObject *kwdict)
{
    static char *kwlist[] = {"string", NULL};
    SHAobject *new;
    Py_buffer buf = { 0 };

    if (!PyArg_ParseTupleAndKeywords(args, kwdict, "|s*:new", kwlist,
                                     &buf)) {
        return NULL;
    }

    if ((new = newSHA224object()) == NULL) {
        PyBuffer_Release(&buf);
        return NULL;
    }

    sha224_init(new);

    if (PyErr_Occurred()) {
        Py_DECREF(new);
        PyBuffer_Release(&buf);
        return NULL;
    }
    if (buf.len > 0) {
        sha_update(new, buf.buf, buf.len);
    }
    PyBuffer_Release(&buf);

    return (PyObject *)new;
}
