array_ass_item(arrayobject *a, Py_ssize_t i, PyObject *v)
{
    if (i < 0 || i >= Py_SIZE(a)) {
        PyErr_SetString(PyExc_IndexError,
                         "array assignment index out of range");
        return -1;
    }
    if (v == NULL)
        return array_ass_slice(a, i, i+1, v);
    return (*a->ob_descr->setitem)(a, i, v);
}
