function_call(PyObject *func, PyObject *arg, PyObject *kw)
{
    PyObject *result;
    PyObject *argdefs;
    PyObject *kwtuple = NULL;
    PyObject **d, **k;
    Py_ssize_t nk, nd;

    argdefs = PyFunction_GET_DEFAULTS(func);
    if (argdefs != NULL && PyTuple_Check(argdefs)) {
        d = &PyTuple_GET_ITEM((PyTupleObject *)argdefs, 0);
        nd = PyTuple_GET_SIZE(argdefs);
    }
    else {
        d = NULL;
        nd = 0;
    }

    if (kw != NULL && PyDict_Check(kw)) {
        Py_ssize_t pos, i;
        nk = PyDict_Size(kw);
        kwtuple = PyTuple_New(2*nk);
        if (kwtuple == NULL)
            return NULL;
        k = &PyTuple_GET_ITEM(kwtuple, 0);
        pos = i = 0;
        while (PyDict_Next(kw, &pos, &k[i], &k[i+1])) {
            Py_INCREF(k[i]);
            Py_INCREF(k[i+1]);
            i += 2;
        }
        nk = i/2;
    }
    else {
        k = NULL;
        nk = 0;
    }

    result = PyEval_EvalCodeEx(
        PyFunction_GET_CODE(func),
        PyFunction_GET_GLOBALS(func), (PyObject *)NULL,
        &PyTuple_GET_ITEM(arg, 0), PyTuple_GET_SIZE(arg),
        k, nk, d, nd,
        PyFunction_GET_KW_DEFAULTS(func),
        PyFunction_GET_CLOSURE(func));

    Py_XDECREF(kwtuple);

    return result;
}
