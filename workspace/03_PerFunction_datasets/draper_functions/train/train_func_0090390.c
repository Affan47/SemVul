list_ass_item(PyListObject *a, Py_ssize_t i, PyObject *v)
{
    PyObject *old_value;
    if (i < 0 || i >= Py_SIZE(a)) {
        PyErr_SetString(PyExc_IndexError,
                        "list assignment index out of range");
        return -1;
    }
    if (v == NULL)
        return list_ass_slice(a, i, i+1, v);
    Py_INCREF(v);
    old_value = a->ob_item[i];
    a->ob_item[i] = v;
    Py_DECREF(old_value);
    return 0;
}
