PyList_Reverse(PyObject *v)
{
    PyListObject *self = (PyListObject *)v;

    if (v == NULL || !PyList_Check(v)) {
        PyErr_BadInternalCall();
        return -1;
    }
    if (Py_SIZE(self) > 1)
        reverse_slice(self->ob_item, self->ob_item + Py_SIZE(self));
    return 0;
}
