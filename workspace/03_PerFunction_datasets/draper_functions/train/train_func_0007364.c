builtin_getattr(PyObject *self, PyObject *args)
{
    PyObject *v, *result, *dflt = NULL;
    PyObject *name;

    if (!PyArg_UnpackTuple(args, "getattr", 2, 3, &v, &name, &dflt))
        return NULL;

    if (!PyUnicode_Check(name)) {
        PyErr_SetString(PyExc_TypeError,
                        "getattr(): attribute name must be string");
        return NULL;
    }
    result = PyObject_GetAttr(v, name);
    if (result == NULL && dflt != NULL &&
        PyErr_ExceptionMatches(PyExc_AttributeError))
    {
        PyErr_Clear();
        Py_INCREF(dflt);
        result = dflt;
    }
    return result;
}
