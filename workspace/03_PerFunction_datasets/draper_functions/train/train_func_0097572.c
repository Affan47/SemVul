PyImport_AddModule(const char *name)
{
    PyObject *nameobj, *module;
    nameobj = PyUnicode_FromString(name);
    if (nameobj == NULL)
        return NULL;
    module = PyImport_AddModuleObject(nameobj);
    Py_DECREF(nameobj);
    return module;
}
