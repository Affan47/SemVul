Py_ReprEnter(PyObject *obj)
{
    PyObject *dict;
    PyObject *list;
    Py_ssize_t i;

    dict = PyThreadState_GetDict();
    if (dict == NULL)
        return 0;
    list = PyDict_GetItemString(dict, KEY);
    if (list == NULL) {
        list = PyList_New(0);
        if (list == NULL)
            return -1;
        if (PyDict_SetItemString(dict, KEY, list) < 0)
            return -1;
        Py_DECREF(list);
    }
    i = PyList_GET_SIZE(list);
    while (--i >= 0) {
        if (PyList_GET_ITEM(list, i) == obj)
            return 1;
    }
    PyList_Append(list, obj);
    return 0;
}
