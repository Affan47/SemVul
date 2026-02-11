_progress_handler(void* user_arg)
{
    int rc;
    PyObject *ret;
#ifdef WITH_THREAD
    PyGILState_STATE gilstate;

    gilstate = PyGILState_Ensure();
#endif
    ret = PyObject_CallFunction((PyObject*)user_arg, "");

    if (!ret) {
        if (_enable_callback_tracebacks) {
            PyErr_Print();
        } else {
            PyErr_Clear();
        }


        rc = 1;
    } else {
        rc = (int)PyObject_IsTrue(ret);
        Py_DECREF(ret);
    }

#ifdef WITH_THREAD
    PyGILState_Release(gilstate);
#endif
    return rc;
}
