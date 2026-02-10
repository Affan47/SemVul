chain_new_from_iterable(PyTypeObject *type, PyObject *arg)
{
    PyObject *source;

    source = PyObject_GetIter(arg);
    if (source == NULL)
        return NULL;

    return chain_new_internal(type, source);
}
