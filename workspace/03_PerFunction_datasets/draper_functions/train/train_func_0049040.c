weakref_getweakrefcount(PyObject *self, PyObject *object)
{
    PyObject *result = NULL;

    if (PyType_SUPPORTS_WEAKREFS(Py_TYPE(object))) {
        PyWeakReference **list = GET_WEAKREFS_LISTPTR(object);

        result = PyLong_FromSsize_t(_PyWeakref_GetWeakrefCount(*list));
    }
    else
        result = PyLong_FromLong(0);

    return result;
}
