PyNumber_ToBase(PyObject *n, int base)
{
    PyObject *res = NULL;
    PyObject *index = PyNumber_Index(n);

    if (!index)
        return NULL;
    if (PyLong_Check(index))
        res = _PyLong_Format(index, base);
    else


        PyErr_SetString(PyExc_ValueError, "PyNumber_ToBase: index not int");
    Py_DECREF(index);
    return res;
}
