array_item(arrayobject *a, Py_ssize_t i)
{
    if (i < 0 || i >= Py_SIZE(a)) {
        PyErr_SetString(PyExc_IndexError, "array index out of range");
        return NULL;
    }
    return getarrayitem((PyObject *)a, i);
}
