bytesio_getstate(bytesio *self)
{
    PyObject *initvalue = bytesio_getvalue(self);
    PyObject *dict;
    PyObject *state;

    if (initvalue == NULL)
        return NULL;
    if (self->dict == NULL) {
        Py_INCREF(Py_None);
        dict = Py_None;
    }
    else {
        dict = PyDict_Copy(self->dict);
        if (dict == NULL) {
            Py_DECREF(initvalue);
            return NULL;
        }
    }

    state = Py_BuildValue("(OnN)", initvalue, self->pos, dict);
    Py_DECREF(initvalue);
    return state;
}
