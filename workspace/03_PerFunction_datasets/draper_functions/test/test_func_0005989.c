list_join(PyObject* list)
{


    PyObject* joiner;
    PyObject* function;
    PyObject* args;
    PyObject* result;

    switch (PyList_GET_SIZE(list)) {
    case 0:
        Py_DECREF(list);
        return PyBytes_FromString("");
    case 1:
        result = PyList_GET_ITEM(list, 0);
        Py_INCREF(result);
        Py_DECREF(list);
        return result;
    }


    joiner = PySequence_GetSlice(PyList_GET_ITEM(list, 0), 0, 0);
    if (!joiner)
        return NULL;

    function = PyObject_GetAttrString(joiner, "join");
    if (!function) {
        Py_DECREF(joiner);
        return NULL;
    }

    args = PyTuple_New(1);
    if (!args)
        return NULL;

    PyTuple_SET_ITEM(args, 0, list);

    result = PyObject_CallObject(function, args);

    Py_DECREF(args);
    Py_DECREF(function);
    Py_DECREF(joiner);

    return result;
}
