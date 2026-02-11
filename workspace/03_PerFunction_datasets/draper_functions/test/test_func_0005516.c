addressof(PyObject *self, PyObject *obj)
{
    if (CDataObject_Check(obj))
        return PyLong_FromVoidPtr(((CDataObject *)obj)->b_ptr);
    PyErr_SetString(PyExc_TypeError,
                    "invalid type");
    return NULL;
}
