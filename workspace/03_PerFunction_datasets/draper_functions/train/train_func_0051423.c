fast_save_leave(Picklerobject *self, PyObject *obj)
{
    if (self->fast_container-- >= PY_CPICKLE_FAST_LIMIT) {
        PyObject *key = PyLong_FromVoidPtr(obj);
        if (key == NULL)
            return 0;
        if (PyDict_DelItem(self->fast_memo, key) < 0) {
            Py_DECREF(key);
            return 0;
        }
        Py_DECREF(key);
    }
    return 1;
}
