Unpickler_setattr(Unpicklerobject *self, char *name, PyObject *value)
{

    if (!strcmp(name, "persistent_load")) {
        Py_XDECREF(self->pers_func);
        self->pers_func = value;
        Py_XINCREF(value);
        return 0;
    }

    if (!strcmp(name, "find_global")) {
        Py_XDECREF(self->find_class);
        self->find_class = value;
        Py_XINCREF(value);
        return 0;
    }

    if (! value) {
        PyErr_SetString(PyExc_TypeError,
                        "attribute deletion is not supported");
        return -1;
    }

    if (strcmp(name, "memo") == 0) {
        if (!PyDict_Check(value)) {
            PyErr_SetString(PyExc_TypeError,
                            "memo must be a dictionary");
            return -1;
        }
        Py_XDECREF(self->memo);
        self->memo = value;
        Py_INCREF(value);
        return 0;
    }

    PyErr_SetString(PyExc_AttributeError, name);
    return -1;
}
