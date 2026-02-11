EnvironmentError_reduce(PyEnvironmentErrorObject *self)
{
    PyObject *args = self->args;
    PyObject *res = NULL, *tmp;


    if (PyTuple_GET_SIZE(args) == 2 && self->filename) {
        args = PyTuple_New(3);
        if (!args)
            return NULL;

        tmp = PyTuple_GET_ITEM(self->args, 0);
        Py_INCREF(tmp);
        PyTuple_SET_ITEM(args, 0, tmp);

        tmp = PyTuple_GET_ITEM(self->args, 1);
        Py_INCREF(tmp);
        PyTuple_SET_ITEM(args, 1, tmp);

        Py_INCREF(self->filename);
        PyTuple_SET_ITEM(args, 2, self->filename);
    } else
        Py_INCREF(args);

    if (self->dict)
        res = PyTuple_Pack(3, Py_TYPE(self), args, self->dict);
    else
        res = PyTuple_Pack(2, Py_TYPE(self), args);
    Py_DECREF(args);
    return res;
}
