PyThreadState_DeleteCurrent()
{
    PyThreadState *tstate = _PyThreadState_Current;
    if (tstate == NULL)
        Py_FatalError(
            "PyThreadState_DeleteCurrent: no current tstate");
    _PyThreadState_Current = NULL;
    tstate_delete_common(tstate);
    if (autoInterpreterState && PyThread_get_key_value(autoTLSkey) == tstate)
        PyThread_delete_key_value(autoTLSkey);
    PyEval_ReleaseLock();
}
