BaseException_set_cause(PyObject *self, PyObject *arg) {
    if (arg == NULL) {
        PyErr_SetString(PyExc_TypeError, "__cause__ may not be deleted");
        return -1;
    } else if (arg == Py_None) {
        arg = NULL;
    } else if (!PyExceptionInstance_Check(arg)) {
        PyErr_SetString(PyExc_TypeError, "exception cause must be None "
                        "or derive from BaseException");
        return -1;
    } else {

        Py_INCREF(arg);
    }
    PyException_SetCause(self, arg);
    return 0;
}
