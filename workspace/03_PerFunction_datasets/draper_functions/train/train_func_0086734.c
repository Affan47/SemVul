PyType_Modified(PyTypeObject *type)
{


    PyObject *raw, *ref;
    Py_ssize_t i, n;

    if (!PyType_HasFeature(type, Py_TPFLAGS_VALID_VERSION_TAG))
        return;

    raw = type->tp_subclasses;
    if (raw != NULL) {
        n = PyList_GET_SIZE(raw);
        for (i = 0; i < n; i++) {
            ref = PyList_GET_ITEM(raw, i);
            ref = PyWeakref_GET_OBJECT(ref);
            if (ref != Py_None) {
                PyType_Modified((PyTypeObject *)ref);
            }
        }
    }
    type->tp_flags &= ~Py_TPFLAGS_VALID_VERSION_TAG;
}
