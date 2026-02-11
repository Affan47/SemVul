pending_threadfunc(PyObject *self, PyObject *arg)
{
    PyObject *callable;
    int r;
    if (PyArg_ParseTuple(arg, "O", &callable) == 0)
        return NULL;


    Py_INCREF(callable);

    Py_BEGIN_ALLOW_THREADS
    r = Py_AddPendingCall(&_pending_callback, callable);
    Py_END_ALLOW_THREADS

    if (r<0) {
        Py_DECREF(callable);
        Py_INCREF(Py_False);
        return Py_False;
    }
    Py_INCREF(Py_True);
    return Py_True;
}
