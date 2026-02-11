Py_NewInterpreter(void)
{
    PyInterpreterState *interp;
    PyThreadState *tstate, *save_tstate;
    PyObject *bimod, *sysmod;

    if (!initialized)
        Py_FatalError("Py_NewInterpreter: call Py_Initialize first");

    interp = PyInterpreterState_New();
    if (interp == NULL)
        return NULL;

    tstate = PyThreadState_New(interp);
    if (tstate == NULL) {
        PyInterpreterState_Delete(interp);
        return NULL;
    }

    save_tstate = PyThreadState_Swap(tstate);


    interp->modules = PyDict_New();

    bimod = _PyImport_FindBuiltin("builtins");
    if (bimod != NULL) {
        interp->builtins = PyModule_GetDict(bimod);
        if (interp->builtins == NULL)
            goto handle_error;
        Py_INCREF(interp->builtins);
    }


    _PyExc_Init(bimod);

    sysmod = _PyImport_FindBuiltin("sys");
    if (bimod != NULL && sysmod != NULL) {
        PyObject *pstderr;

        interp->sysdict = PyModule_GetDict(sysmod);
        if (interp->sysdict == NULL)
            goto handle_error;
        Py_INCREF(interp->sysdict);
        PySys_SetPath(Py_GetPath());
        PyDict_SetItemString(interp->sysdict, "modules",
                             interp->modules);


        pstderr = PyFile_NewStdPrinter(fileno(stderr));
        if (pstderr == NULL)
            Py_FatalError("Py_Initialize: can't set preliminary stderr");
        _PySys_SetObjectId(&PyId_stderr, pstderr);
        PySys_SetObject("__stderr__", pstderr);
        Py_DECREF(pstderr);

        _PyImportHooks_Init();

        import_init(interp, sysmod);

        if (initfsencoding(interp) < 0)
            goto handle_error;

        if (initstdio() < 0)
            Py_FatalError(
            "Py_Initialize: can't initialize sys standard streams");
        initmain(interp);
        if (!Py_NoSiteFlag)
            initsite();
    }

    if (!PyErr_Occurred())
        return tstate;

handle_error:


    PyErr_PrintEx(0);
    PyThreadState_Clear(tstate);
    PyThreadState_Swap(save_tstate);
    PyThreadState_Delete(tstate);
    PyInterpreterState_Delete(interp);

    return NULL;
}
