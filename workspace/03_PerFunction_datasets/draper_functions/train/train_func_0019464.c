EVP_new(PyObject *self, PyObject *args, PyObject *kwdict)
{
    static char *kwlist[] = {"name", "string", NULL};
    PyObject *name_obj = NULL;
    PyObject *data_obj = NULL;
    Py_buffer view = { 0 };
    PyObject *ret_obj;
    char *name;
    const EVP_MD *digest;

    if (!PyArg_ParseTupleAndKeywords(args, kwdict, "O|O:new", kwlist,
                                     &name_obj, &data_obj)) {
        return NULL;
    }

    if (!PyArg_Parse(name_obj, "s", &name)) {
        PyErr_SetString(PyExc_TypeError, "name must be a string");
        return NULL;
    }

    if (data_obj)
        GET_BUFFER_VIEW_OR_ERROUT(data_obj, &view);

    digest = EVP_get_digestbyname(name);

    ret_obj = EVPnew(name_obj, digest, NULL, (unsigned char*)view.buf, view.len);

    if (data_obj)
        PyBuffer_Release(&view);
    return ret_obj;
}
