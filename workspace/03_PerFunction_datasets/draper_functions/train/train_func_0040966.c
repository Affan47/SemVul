set_reduce(PySetObject *so)
{
    PyObject *keys=NULL, *args=NULL, *result=NULL, *dict=NULL;

    keys = PySequence_List((PyObject *)so);
    if (keys == NULL)
        goto done;
    args = PyTuple_Pack(1, keys);
    if (args == NULL)
        goto done;
    dict = PyObject_GetAttrString((PyObject *)so, "__dict__");
    if (dict == NULL) {
        PyErr_Clear();
        dict = Py_None;
        Py_INCREF(dict);
    }
    result = PyTuple_Pack(3, Py_TYPE(so), args, dict);
done:
    Py_XDECREF(args);
    Py_XDECREF(keys);
    Py_XDECREF(dict);
    return result;
}
