_dir_object(PyObject *obj)
{
    PyObject *result, *sorted;
    PyObject *dirfunc = _PyObject_LookupSpecial(obj, &PyId___dir__);

    assert(obj);
    if (dirfunc == NULL) {
        if (!PyErr_Occurred())
            PyErr_SetString(PyExc_TypeError, "object does not provide __dir__");
        return NULL;
    }

    result = PyObject_CallFunctionObjArgs(dirfunc, NULL);
    Py_DECREF(dirfunc);
    if (result == NULL)
        return NULL;

    sorted = PySequence_List(result);
    Py_DECREF(result);
    if (sorted == NULL)
        return NULL;
    if (PyList_Sort(sorted)) {
        Py_DECREF(sorted);
        return NULL;
    }
    return sorted;
}
