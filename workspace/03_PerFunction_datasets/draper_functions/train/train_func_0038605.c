PyInstance_NewRaw(PyObject *klass, PyObject *dict)
{
    PyInstanceObject *inst;

    if (!PyClass_Check(klass)) {
        PyErr_BadInternalCall();
        return NULL;
    }
    if (dict == NULL) {
        dict = PyDict_New();
        if (dict == NULL)
            return NULL;
    }
    else {
        if (!PyDict_Check(dict)) {
            PyErr_BadInternalCall();
            return NULL;
        }
        Py_INCREF(dict);
    }
    inst = PyObject_GC_New(PyInstanceObject, &PyInstance_Type);
    if (inst == NULL) {
        Py_DECREF(dict);
        return NULL;
    }
    inst->in_weakreflist = NULL;
    Py_INCREF(klass);
    inst->in_class = (PyClassObject *)klass;
    inst->in_dict = dict;
    _PyObject_GC_TRACK(inst);
    return (PyObject *)inst;
}
