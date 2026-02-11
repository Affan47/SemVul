pyepoll_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    int flags = 0, sizehint = FD_SETSIZE - 1;
    static char *kwlist[] = {"sizehint", "flags", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|ii:epoll", kwlist,
                                     &sizehint, &flags))
        return NULL;
    if (sizehint < 0) {
        PyErr_SetString(PyExc_ValueError, "negative sizehint");
        return NULL;
    }

    return newPyEpoll_Object(type, sizehint, flags, -1);
}
