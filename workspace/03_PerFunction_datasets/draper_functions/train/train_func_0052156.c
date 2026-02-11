poll_poll(pollObject *self, PyObject *args)
{
    PyObject *result_list = NULL, *tout = NULL;
    int timeout = 0, poll_result, i, j;
    PyObject *value = NULL, *num = NULL;

    if (!PyArg_UnpackTuple(args, "poll", 0, 1, &tout)) {
        return NULL;
    }


    if (tout == NULL || tout == Py_None)
        timeout = -1;
    else if (!PyNumber_Check(tout)) {
        PyErr_SetString(PyExc_TypeError,
                        "timeout must be an integer or None");
        return NULL;
    }
    else {
        tout = PyNumber_Long(tout);
        if (!tout)
            return NULL;
        timeout = _PyLong_AsInt(tout);
        Py_DECREF(tout);
        if (timeout == -1 && PyErr_Occurred())
            return NULL;
    }


    if (self->poll_running) {
        PyErr_SetString(PyExc_RuntimeError,
                        "concurrent poll() invocation");
        return NULL;
    }


    if (!self->ufd_uptodate)
        if (update_ufd_array(self) == 0)
            return NULL;

    self->poll_running = 1;


    Py_BEGIN_ALLOW_THREADS
    poll_result = poll(self->ufds, self->ufd_len, timeout);
    Py_END_ALLOW_THREADS

    self->poll_running = 0;

    if (poll_result < 0) {
        PyErr_SetFromErrno(PyExc_OSError);
        return NULL;
    }


    result_list = PyList_New(poll_result);
    if (!result_list)
        return NULL;
    else {
        for (i = 0, j = 0; j < poll_result; j++) {

            while (!self->ufds[i].revents) {
                i++;
            }


            value = PyTuple_New(2);
            if (value == NULL)
                goto error;
            num = PyLong_FromLong(self->ufds[i].fd);
            if (num == NULL) {
                Py_DECREF(value);
                goto error;
            }
            PyTuple_SET_ITEM(value, 0, num);


            num = PyLong_FromLong(self->ufds[i].revents & 0xffff);
            if (num == NULL) {
                Py_DECREF(value);
                goto error;
            }
            PyTuple_SET_ITEM(value, 1, num);
            if ((PyList_SetItem(result_list, j, value)) == -1) {
                Py_DECREF(value);
                goto error;
            }
            i++;
        }
    }
    return result_list;

  error:
    Py_DECREF(result_list);
    return NULL;
}
