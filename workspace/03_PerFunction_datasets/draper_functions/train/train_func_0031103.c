element_get(ElementObject* self, PyObject* args)
{
    PyObject* value;

    PyObject* key;
    PyObject* default_value = Py_None;
    if (!PyArg_ParseTuple(args, "O|O:get", &key, &default_value))
        return NULL;

    if (!self->extra || self->extra->attrib == Py_None)
        value = default_value;
    else {
        value = PyDict_GetItem(self->extra->attrib, key);
        if (!value)
            value = default_value;
    }

    Py_INCREF(value);
    return value;
}
