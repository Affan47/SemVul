sys_exc_clear(PyObject *self, PyObject *noargs)
{
    PyThreadState *tstate;
    PyObject *tmp_type, *tmp_value, *tmp_tb;

    if (PyErr_WarnPy3k("sys.exc_clear() not supported in 3.x; "
                       "use except clauses", 1) < 0)
        return NULL;

    tstate = PyThreadState_GET();
    tmp_type = tstate->exc_type;
    tmp_value = tstate->exc_value;
    tmp_tb = tstate->exc_traceback;
    tstate->exc_type = NULL;
    tstate->exc_value = NULL;
    tstate->exc_traceback = NULL;
    Py_XDECREF(tmp_type);
    Py_XDECREF(tmp_value);
    Py_XDECREF(tmp_tb);

    PySys_SetObject("exc_type", Py_None);
    PySys_SetObject("exc_value", Py_None);
    PySys_SetObject("exc_traceback", Py_None);
    Py_INCREF(Py_None);
    return Py_None;
}
