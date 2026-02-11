calliter_iternext(calliterobject *it)
{
    if (it->it_callable != NULL) {
        PyObject *args = PyTuple_New(0);
        PyObject *result;
        if (args == NULL)
            return NULL;
        result = PyObject_Call(it->it_callable, args, NULL);
        Py_DECREF(args);
        if (result != NULL) {
            int ok;
            ok = PyObject_RichCompareBool(it->it_sentinel, result, Py_EQ);
            if (ok == 0)
                return result;
            Py_DECREF(result);
            if (ok > 0) {
                Py_CLEAR(it->it_callable);
                Py_CLEAR(it->it_sentinel);
            }
        }
        else if (PyErr_ExceptionMatches(PyExc_StopIteration)) {
            PyErr_Clear();
            Py_CLEAR(it->it_callable);
            Py_CLEAR(it->it_sentinel);
        }
    }
    return NULL;
}
