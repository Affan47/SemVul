marshal_dumps(PyObject *self, PyObject *args)
{
    PyObject *x;
    int version = Py_MARSHAL_VERSION;
    if (!PyArg_ParseTuple(args, "O|i:dumps", &x, &version))
        return NULL;
    return PyMarshal_WriteObjectToString(x, version);
}
