PyEval_ReInitThreads(void)
{
    PyObject *threading, *result;
    PyThreadState *tstate;

    if (!interpreter_lock)
        return;


    interpreter_lock = PyThread_allocate_lock();
    pending_lock = PyThread_allocate_lock();
    PyThread_acquire_lock(interpreter_lock, 1);
    main_thread = PyThread_get_thread_ident();


    tstate = PyThreadState_GET();
    threading = PyMapping_GetItemString(tstate->interp->modules,
                                        "threading");
    if (threading == NULL) {

        PyErr_Clear();
        return;
    }
    result = PyObject_CallMethod(threading, "_after_fork", NULL);
    if (result == NULL)
        PyErr_WriteUnraisable(threading);
    else
        Py_DECREF(result);
    Py_DECREF(threading);
}
