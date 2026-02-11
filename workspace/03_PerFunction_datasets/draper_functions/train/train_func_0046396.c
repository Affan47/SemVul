trace_trampoline(PyObject *self, PyFrameObject *frame,
                 int what, PyObject *arg)
{
    PyThreadState *tstate = frame->f_tstate;
    PyObject *callback;
    PyObject *result;

    if (what == PyTrace_CALL)
        callback = self;
    else
        callback = frame->f_trace;
    if (callback == NULL)
        return 0;
    result = call_trampoline(tstate, callback, frame, what, arg);
    if (result == NULL) {
        PyEval_SetTrace(NULL, NULL);
        Py_CLEAR(frame->f_trace);
        return -1;
    }
    if (result != Py_None) {
        PyObject *temp = frame->f_trace;
        frame->f_trace = NULL;
        Py_XDECREF(temp);
        frame->f_trace = result;
    }
    else {
        Py_DECREF(result);
    }
    return 0;
}
