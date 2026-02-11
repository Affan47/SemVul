builtin_hasattr(PyObject *self, PyObject *args)
{
    PyObject *v;
    PyObject *name;

    if (!PyArg_UnpackTuple(args, "hasattr", 2, 2, &v, &name))
        return NULL;
#ifdef Py_USING_UNICODE
    if (PyUnicode_Check(name)) {
        name = _PyUnicode_AsDefaultEncodedString(name, NULL);
        if (name == NULL)
            return NULL;
    }
#endif

    if (!PyString_Check(name)) {
        PyErr_SetString(PyExc_TypeError,
                        "hasattr(): attribute name must be string");
        return NULL;
    }
    v = PyObject_GetAttr(v, name);
    if (v == NULL) {
        if (!PyErr_ExceptionMatches(PyExc_Exception))
            return NULL;
        else {
            PyErr_Clear();
            Py_INCREF(Py_False);
            return Py_False;
        }
    }
    Py_DECREF(v);
    Py_INCREF(Py_True);
    return Py_True;
}
