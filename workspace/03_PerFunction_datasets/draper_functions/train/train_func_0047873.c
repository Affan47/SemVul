PyImport_ExecCodeModuleWithPathnames(const char *name, PyObject *co,
                                     const char *pathname,
                                     const char *cpathname)
{
    PyObject *m = NULL;
    PyObject *nameobj, *pathobj = NULL, *cpathobj = NULL;

    nameobj = PyUnicode_FromString(name);
    if (nameobj == NULL)
        return NULL;

    if (cpathname != NULL) {
        cpathobj = PyUnicode_DecodeFSDefault(cpathname);
        if (cpathobj == NULL)
            goto error;
    }
    else
        cpathobj = NULL;

    if (pathname != NULL) {
        pathobj = PyUnicode_DecodeFSDefault(pathname);
        if (pathobj == NULL)
            goto error;
    }
    else if (cpathobj != NULL) {
        PyInterpreterState *interp = PyThreadState_GET()->interp;
        _Py_IDENTIFIER(_get_sourcefile);

        if (interp == NULL) {
            Py_FatalError("PyImport_ExecCodeModuleWithPathnames: "
                          "no interpreter!");
        }

        pathobj = _PyObject_CallMethodIdObjArgs(interp->importlib,
                                                &PyId__get_sourcefile, cpathobj,
                                                NULL);
        if (pathobj == NULL)
            PyErr_Clear();
    }
    else
        pathobj = NULL;

    m = PyImport_ExecCodeModuleObject(nameobj, co, pathobj, cpathobj);
error:
    Py_DECREF(nameobj);
    Py_XDECREF(pathobj);
    Py_XDECREF(cpathobj);
    return m;
}
