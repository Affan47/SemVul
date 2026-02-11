fsconvert_strdup(PyObject *o, char**out)
{
    PyObject *bytes;
    Py_ssize_t size;
    if (!PyUnicode_FSConverter(o, &bytes))
        return 0;
    size = PyBytes_GET_SIZE(bytes);
    *out = PyMem_Malloc(size+1);
    if (!*out)
        return 0;
    memcpy(*out, PyBytes_AsString(bytes), size+1);
    Py_DECREF(bytes);
    return 1;
}
