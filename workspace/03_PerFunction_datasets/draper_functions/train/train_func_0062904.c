set_repr(PySetObject *so)
{
    PyObject *keys, *result=NULL, *listrepr;
    int status = Py_ReprEnter((PyObject*)so);

    if (status != 0) {
        if (status < 0)
            return NULL;
        return PyString_FromFormat("%s(...)", so->ob_type->tp_name);
    }

    keys = PySequence_List((PyObject *)so);
    if (keys == NULL)
        goto done;
    listrepr = PyObject_Repr(keys);
    Py_DECREF(keys);
    if (listrepr == NULL)
        goto done;

    result = PyString_FromFormat("%s(%s)", so->ob_type->tp_name,
        PyString_AS_STRING(listrepr));
    Py_DECREF(listrepr);
done:
    Py_ReprLeave((PyObject*)so);
    return result;
}
