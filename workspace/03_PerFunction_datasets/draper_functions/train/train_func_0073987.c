imap_next(imapobject *lz)
{
    PyObject *val;
    PyObject *argtuple;
    PyObject *result;
    Py_ssize_t numargs, i;

    numargs = PyTuple_Size(lz->iters);
    argtuple = PyTuple_New(numargs);
    if (argtuple == NULL)
        return NULL;

    for (i=0 ; i<numargs ; i++) {
        val = PyIter_Next(PyTuple_GET_ITEM(lz->iters, i));
        if (val == NULL) {
            Py_DECREF(argtuple);
            return NULL;
        }
        PyTuple_SET_ITEM(argtuple, i, val);
    }
    if (lz->func == Py_None)
        return argtuple;
    result = PyObject_Call(lz->func, argtuple, NULL);
    Py_DECREF(argtuple);
    return result;
}
