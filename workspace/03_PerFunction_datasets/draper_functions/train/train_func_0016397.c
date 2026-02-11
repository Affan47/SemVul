recurse_down_subclasses(PyTypeObject *type, PyObject *name,
                        update_callback callback, void *data)
{
    PyTypeObject *subclass;
    PyObject *ref, *subclasses, *dict;
    Py_ssize_t i;

    subclasses = type->tp_subclasses;
    if (subclasses == NULL)
        return 0;
    assert(PyDict_CheckExact(subclasses));
    i = 0;
    while (PyDict_Next(subclasses, &i, NULL, &ref)) {
        assert(PyWeakref_CheckRef(ref));
        subclass = (PyTypeObject *)PyWeakref_GET_OBJECT(ref);
        assert(subclass != NULL);
        if ((PyObject *)subclass == Py_None)
            continue;
        assert(PyType_Check(subclass));

        dict = subclass->tp_dict;
        if (dict != NULL && PyDict_Check(dict) &&
            PyDict_GetItem(dict, name) != NULL)
            continue;
        if (update_subclasses(subclass, name, callback, data) < 0)
            return -1;
    }
    return 0;
}
