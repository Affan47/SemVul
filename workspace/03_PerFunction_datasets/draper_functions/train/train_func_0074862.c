callSuper(PyTypeObject *type, PyObject *self,
                    const char *name, PyObject *args, int cardinality)
{
#if PY_VERSION_HEX < 0x02040000
    PyObject *tuple = Py_BuildValue("(OO)", type, self);
#else
    PyObject *tuple = PyTuple_Pack(2, type, self);
#endif
    PyObject *super = PyObject_Call((PyObject *) &PySuper_Type, tuple, NULL);
    PyObject *method, *value;

    Py_DECREF(tuple);
    if (!super)
        return NULL;

    method = PyObject_GetAttrString(super, (char *) name);
    Py_DECREF(super);
    if (!method)
        return NULL;

    if (cardinality > 1)
        value = PyObject_Call(method, args, NULL);
    else
    {
#if PY_VERSION_HEX < 0x02040000
        tuple = Py_BuildValue("(O)", args);
#else
        tuple = PyTuple_Pack(1, args);
#endif
        value = PyObject_Call(method, tuple, NULL);
        Py_DECREF(tuple);
    }

    Py_DECREF(method);

    return value;
}
