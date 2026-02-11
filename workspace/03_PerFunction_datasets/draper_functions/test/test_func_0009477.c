code_new(PyTypeObject *type, PyObject *args, PyObject *kw)
{
    int argcount;
    int nlocals;
    int stacksize;
    int flags;
    PyObject *co = NULL;
    PyObject *code;
    PyObject *consts;
    PyObject *names, *ournames = NULL;
    PyObject *varnames, *ourvarnames = NULL;
    PyObject *freevars = NULL, *ourfreevars = NULL;
    PyObject *cellvars = NULL, *ourcellvars = NULL;
    PyObject *filename;
    PyObject *name;
    int firstlineno;
    PyObject *lnotab;

    if (!PyArg_ParseTuple(args, "iiiiSO!O!O!SSiS|O!O!:code",
                          &argcount, &nlocals, &stacksize, &flags,
                          &code,
                          &PyTuple_Type, &consts,
                          &PyTuple_Type, &names,
                          &PyTuple_Type, &varnames,
                          &filename, &name,
                          &firstlineno, &lnotab,
                          &PyTuple_Type, &freevars,
                          &PyTuple_Type, &cellvars))
        return NULL;

    if (argcount < 0) {
        PyErr_SetString(
            PyExc_ValueError,
            "code: argcount must not be negative");
        goto cleanup;
    }

    if (nlocals < 0) {
        PyErr_SetString(
            PyExc_ValueError,
            "code: nlocals must not be negative");
        goto cleanup;
    }

    ournames = validate_and_copy_tuple(names);
    if (ournames == NULL)
        goto cleanup;
    ourvarnames = validate_and_copy_tuple(varnames);
    if (ourvarnames == NULL)
        goto cleanup;
    if (freevars)
        ourfreevars = validate_and_copy_tuple(freevars);
    else
        ourfreevars = PyTuple_New(0);
    if (ourfreevars == NULL)
        goto cleanup;
    if (cellvars)
        ourcellvars = validate_and_copy_tuple(cellvars);
    else
        ourcellvars = PyTuple_New(0);
    if (ourcellvars == NULL)
        goto cleanup;

    co = (PyObject *)PyCode_New(argcount, nlocals, stacksize, flags,
                                code, consts, ournames, ourvarnames,
                                ourfreevars, ourcellvars, filename,
                                name, firstlineno, lnotab);
  cleanup:
    Py_XDECREF(ournames);
    Py_XDECREF(ourvarnames);
    Py_XDECREF(ourfreevars);
    Py_XDECREF(ourcellvars);
    return co;
}
