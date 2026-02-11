ctx_canonical(PyObject *context UNUSED, PyObject *v)
{
    if (!PyDec_Check(v)) {
        PyErr_SetString(PyExc_TypeError,
            "argument must be a Decimal");
        return NULL;
    }

    Py_INCREF(v);
    return v;
}
