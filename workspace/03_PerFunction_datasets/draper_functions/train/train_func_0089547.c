sched_param_new(PyTypeObject *type, PyObject *args, PyObject *kwargs)
{
    PyObject *res, *priority;
    static char *kwlist[] = {"sched_priority", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O:sched_param", kwlist, &priority))
        return NULL;
    res = PyStructSequence_New(type);
    if (!res)
        return NULL;
    Py_INCREF(priority);
    PyStructSequence_SET_ITEM(res, 0, priority);
    return res;
}
