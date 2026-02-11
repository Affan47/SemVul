wrap_descr_delete(PyObject *self, PyObject *args, void *wrapped)
{
    descrsetfunc func = (descrsetfunc)wrapped;
    PyObject *obj;
    int ret;

    if (!check_num_args(args, 1))
        return NULL;
    obj = PyTuple_GET_ITEM(args, 0);
    ret = (*func)(self, obj, NULL);
    if (ret < 0)
        return NULL;
    Py_INCREF(Py_None);
    return Py_None;
}
