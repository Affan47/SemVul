_PyEval_CallTracing(PyObject *func, PyObject *args)
{
    PyThreadState *tstate = PyThreadState_GET();
    int save_tracing = tstate->tracing;
    int save_use_tracing = tstate->use_tracing;
    PyObject *result;

    tstate->tracing = 0;
    tstate->use_tracing = ((tstate->c_tracefunc != NULL)
                           || (tstate->c_profilefunc != NULL));
    result = PyObject_Call(func, args, NULL);
    tstate->tracing = save_tracing;
    tstate->use_tracing = save_use_tracing;
    return result;
}
