float_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    PyObject *x = Py_False;
    static char *kwlist[] = {"x", 0};

    if (type != &PyFloat_Type)
        return float_subtype_new(type, args, kwds);
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|O:float", kwlist, &x))
        return NULL;


    if (PyUnicode_CheckExact(x))
        return PyFloat_FromString(x);
    return PyNumber_Float(x);
}
