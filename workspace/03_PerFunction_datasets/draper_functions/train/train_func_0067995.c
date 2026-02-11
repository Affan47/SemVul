SHA256_update(SHAobject *self, PyObject *args)
{
    PyObject *obj;
    Py_buffer buf;

    if (!PyArg_ParseTuple(args, "O:update", &obj))
        return NULL;

    GET_BUFFER_VIEW_OR_ERROUT(obj, &buf);

    sha_update(self, buf.buf, buf.len);

    PyBuffer_Release(&buf);
    Py_INCREF(Py_None);
    return Py_None;
}
