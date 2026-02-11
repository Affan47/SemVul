posix_sched_getparam(PyObject *self, PyObject *args)
{
    pid_t pid;
    struct sched_param param;
    PyObject *res, *priority;

    if (!PyArg_ParseTuple(args, _Py_PARSE_PID ":sched_getparam", &pid))
        return NULL;
    if (sched_getparam(pid, &param))
        return posix_error();
    res = PyStructSequence_New(&SchedParamType);
    if (!res)
        return NULL;
    priority = PyLong_FromLong(param.sched_priority);
    if (!priority) {
        Py_DECREF(res);
        return NULL;
    }
    PyStructSequence_SET_ITEM(res, 0, priority);
    return res;
}
