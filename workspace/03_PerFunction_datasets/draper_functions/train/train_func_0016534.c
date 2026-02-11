mpm_query(PyObject *self, PyObject *code)
{
    int result;

    if (!PyInt_Check(code)) {
        PyErr_SetString(PyExc_TypeError,
                        "The argument must be an integer");
        return NULL;
    }

    ap_mpm_query(PyInt_AS_LONG(code), &result);

    return PyInt_FromLong(result);
}
