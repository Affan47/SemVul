instance_str(PyInstanceObject *inst)
{
    PyObject *func;
    PyObject *res;
    static PyObject *strstr;

    if (strstr == NULL) {
        strstr = PyString_InternFromString("__str__");
        if (strstr == NULL)
            return NULL;
    }
    func = instance_getattr(inst, strstr);
    if (func == NULL) {
        if (!PyErr_ExceptionMatches(PyExc_AttributeError))
            return NULL;
        PyErr_Clear();
        return instance_repr(inst);
    }
    res = PyEval_CallObject(func, (PyObject *)NULL);
    Py_DECREF(func);
    return res;
}
