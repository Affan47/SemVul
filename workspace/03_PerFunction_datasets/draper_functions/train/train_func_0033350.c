BaseException_with_traceback(PyObject *self, PyObject *tb) {
    if (PyException_SetTraceback(self, tb))
        return NULL;

    Py_INCREF(self);
    return self;
}
