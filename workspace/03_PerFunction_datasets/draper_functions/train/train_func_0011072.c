lookup_method(PyObject *self, _Py_Identifier *attrid)
{
    PyObject *res = lookup_maybe(self, attrid);
    if (res == NULL && !PyErr_Occurred())
        PyErr_SetObject(PyExc_AttributeError, attrid->object);
    return res;
}
