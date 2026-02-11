instance_iternext(PyInstanceObject *self)
{
    PyObject *func;

    if (nextstr == NULL) {
        nextstr = PyString_InternFromString("next");
        if (nextstr == NULL)
            return NULL;
    }

    if ((func = instance_getattr(self, nextstr)) != NULL) {
        PyObject *res = PyEval_CallObject(func, (PyObject *)NULL);
        Py_DECREF(func);
        if (res != NULL) {
            return res;
        }
        if (PyErr_ExceptionMatches(PyExc_StopIteration)) {
            PyErr_Clear();
            return NULL;
        }
        return NULL;
    }
    PyErr_SetString(PyExc_TypeError, "instance has no next() method");
    return NULL;
}
