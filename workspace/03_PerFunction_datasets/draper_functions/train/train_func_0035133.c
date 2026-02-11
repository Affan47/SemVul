pyepoll_poll(pyEpoll_Object *self, PyObject *args, PyObject *kwds)
{
    double dtimeout = -1.;
    int timeout;
    int maxevents = -1;
    int nfds, i;
    PyObject *elist = NULL, *etuple = NULL;
    struct epoll_event *evs = NULL;
    static char *kwlist[] = {"timeout", "maxevents", NULL};

    if (self->epfd < 0)
        return pyepoll_err_closed();

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|di:poll", kwlist,
                                     &dtimeout, &maxevents)) {
        return NULL;
    }

    if (dtimeout < 0) {
        timeout = -1;
    }
    else if (dtimeout * 1000.0 > INT_MAX) {
        PyErr_SetString(PyExc_OverflowError,
                        "timeout is too large");
        return NULL;
    }
    else {
        timeout = (int)(dtimeout * 1000.0);
    }

    if (maxevents == -1) {
        maxevents = FD_SETSIZE-1;
    }
    else if (maxevents < 1) {
        PyErr_Format(PyExc_ValueError,
                     "maxevents must be greater than 0, got %d",
                     maxevents);
        return NULL;
    }

    evs = PyMem_New(struct epoll_event, maxevents);
    if (evs == NULL) {
        Py_DECREF(self);
        PyErr_NoMemory();
        return NULL;
    }

    Py_BEGIN_ALLOW_THREADS
    nfds = epoll_wait(self->epfd, evs, maxevents, timeout);
    Py_END_ALLOW_THREADS
    if (nfds < 0) {
        PyErr_SetFromErrno(PyExc_IOError);
        goto error;
    }

    elist = PyList_New(nfds);
    if (elist == NULL) {
        goto error;
    }

    for (i = 0; i < nfds; i++) {
        etuple = Py_BuildValue("iI", evs[i].data.fd, evs[i].events);
        if (etuple == NULL) {
            Py_CLEAR(elist);
            goto error;
        }
        PyList_SET_ITEM(elist, i, etuple);
    }

    error:
    PyMem_Free(evs);
    return elist;
}
