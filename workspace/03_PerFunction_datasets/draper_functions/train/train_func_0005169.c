fileio_repr(fileio *self)
{
    PyObject *nameobj, *res;

    if (self->fd < 0)
        return PyUnicode_FromFormat("<_io.FileIO [closed]>");

    nameobj = _PyObject_GetAttrId((PyObject *) self, &PyId_name);
    if (nameobj == NULL) {
        if (PyErr_ExceptionMatches(PyExc_AttributeError))
            PyErr_Clear();
        else
            return NULL;
        res = PyUnicode_FromFormat("<_io.FileIO fd=%d mode='%s'>",
                                   self->fd, mode_string(self));
    }
    else {
        res = PyUnicode_FromFormat("<_io.FileIO name=%R mode='%s'>",
                                   nameobj, mode_string(self));
        Py_DECREF(nameobj);
    }
    return res;
}
