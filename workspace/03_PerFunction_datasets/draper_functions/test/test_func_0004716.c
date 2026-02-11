t_bootstrap(void *boot_raw)
{
    struct bootstate *boot = (struct bootstate *) boot_raw;
    PyThreadState *tstate;
    PyObject *res;

    tstate = boot->tstate;
    tstate->thread_id = PyThread_get_thread_ident();
    _PyThreadState_Init(tstate);
    PyEval_AcquireThread(tstate);
    nb_threads++;
    res = PyEval_CallObjectWithKeywords(
        boot->func, boot->args, boot->keyw);
    if (res == NULL) {
        if (PyErr_ExceptionMatches(PyExc_SystemExit))
            PyErr_Clear();
        else {
            PyObject *file;
            PyObject *exc, *value, *tb;
            PySys_WriteStderr(
                "Unhandled exception in thread started by ");
            PyErr_Fetch(&exc, &value, &tb);
            file = _PySys_GetObjectId(&PyId_stderr);
            if (file != NULL && file != Py_None)
                PyFile_WriteObject(boot->func, file, 0);
            else
                PyObject_Print(boot->func, stderr, 0);
            PySys_WriteStderr("\n");
            PyErr_Restore(exc, value, tb);
            PyErr_PrintEx(0);
        }
    }
    else
        Py_DECREF(res);
    Py_DECREF(boot->func);
    Py_DECREF(boot->args);
    Py_XDECREF(boot->keyw);
    PyMem_DEL(boot_raw);
    nb_threads--;
    PyThreadState_Clear(tstate);
    PyThreadState_DeleteCurrent();
    PyThread_exit_thread();
}
