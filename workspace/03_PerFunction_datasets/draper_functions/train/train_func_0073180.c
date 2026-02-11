posix__exit(PyObject *self, PyObject *args)
{
    int sts;
    if (!PyArg_ParseTuple(args, "i:_exit", &sts))
        return NULL;
    _exit(sts);
    return NULL;
}
