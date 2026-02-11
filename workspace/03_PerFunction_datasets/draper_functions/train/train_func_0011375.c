PyEval_ReInitThreads(void)
{
    _Py_IDENTIFIER(_after_fork);
    PyObject *threading, *result;
    PyThreadState *tstate = PyThreadState_GET();

    if (!gil_created())
        return;
    recreate_gil();
    pending_lock = PyThread_allocate_lock();
    take_gil(tstate);
    main_thread = PyThread_get_thread_ident();


    tstate = PyThreadState_GET();
    threading = PyMapping_GetItemString(tstate->interp->modules,
                                        "threading");
    if (threading == NULL) {

        PyErr_Clear();
        return;
    }
    result = _PyObject_CallMethodId(threading, &PyId__after_fork, NULL);
    if (result == NULL)
        PyErr_WriteUnraisable(threading);
    else
        Py_DECREF(result);
    Py_DECREF(threading);
}
