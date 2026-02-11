PyCObject_GetDesc(PyObject *self)
{
    if (self) {
        if (self->ob_type == &PyCObject_Type)
            return ((PyCObject *)self)->desc;
        PyErr_SetString(PyExc_TypeError,
                        "PyCObject_GetDesc with non-C-object");
    }
    if (!PyErr_Occurred())
        PyErr_SetString(PyExc_TypeError,
                        "PyCObject_GetDesc called with null pointer");
    return NULL;
}
