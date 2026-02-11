imp_init_frozen(PyObject *self, PyObject *args)
{
    PyObject *name;
    int ret;
    PyObject *m;
    if (!PyArg_ParseTuple(args, "U:init_frozen", &name))
        return NULL;
    ret = PyImport_ImportFrozenModuleObject(name);
    if (ret < 0)
        return NULL;
    if (ret == 0) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    m = PyImport_AddModuleObject(name);
    Py_XINCREF(m);
    return m;
}
