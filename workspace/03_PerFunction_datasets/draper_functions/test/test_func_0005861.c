Pointer_get_contents(CDataObject *self, void *closure)
{
    StgDictObject *stgdict;

    if (*(void **)self->b_ptr == NULL) {
        PyErr_SetString(PyExc_ValueError,
                        "NULL pointer access");
        return NULL;
    }

    stgdict = PyObject_stgdict((PyObject *)self);
    assert(stgdict);
    return PyCData_FromBaseObj(stgdict->proto,
                             (PyObject *)self, 0,
                             *(void **)self->b_ptr);
}
