PySet_Add(PyObject *anyset, PyObject *key)
{
    if (!PySet_Check(anyset) &&
        (!PyFrozenSet_Check(anyset) || Py_REFCNT(anyset) != 1)) {
        PyErr_BadInternalCall();
        return -1;
    }
    return set_add_key((PySetObject *)anyset, key);
}
