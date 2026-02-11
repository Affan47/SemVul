PyCode_New(int argcount, int nlocals, int stacksize, int flags,
           PyObject *code, PyObject *consts, PyObject *names,
           PyObject *varnames, PyObject *freevars, PyObject *cellvars,
           PyObject *filename, PyObject *name, int firstlineno,
           PyObject *lnotab)
{
    PyCodeObject *co;
    Py_ssize_t i;

    if (argcount < 0 || nlocals < 0 ||
        code == NULL ||
        consts == NULL || !PyTuple_Check(consts) ||
        names == NULL || !PyTuple_Check(names) ||
        varnames == NULL || !PyTuple_Check(varnames) ||
        freevars == NULL || !PyTuple_Check(freevars) ||
        cellvars == NULL || !PyTuple_Check(cellvars) ||
        name == NULL || !PyString_Check(name) ||
        filename == NULL || !PyString_Check(filename) ||
        lnotab == NULL || !PyString_Check(lnotab) ||
        !PyObject_CheckReadBuffer(code)) {
        PyErr_BadInternalCall();
        return NULL;
    }
    intern_strings(names);
    intern_strings(varnames);
    intern_strings(freevars);
    intern_strings(cellvars);

    for (i = PyTuple_Size(consts); --i >= 0; ) {
        PyObject *v = PyTuple_GetItem(consts, i);
        if (!PyString_Check(v))
            continue;
        if (!all_name_chars((unsigned char *)PyString_AS_STRING(v)))
            continue;
        PyString_InternInPlace(&PyTuple_GET_ITEM(consts, i));
    }
    co = PyObject_NEW(PyCodeObject, &PyCode_Type);
    if (co != NULL) {
        co->co_argcount = argcount;
        co->co_nlocals = nlocals;
        co->co_stacksize = stacksize;
        co->co_flags = flags;
        Py_INCREF(code);
        co->co_code = code;
        Py_INCREF(consts);
        co->co_consts = consts;
        Py_INCREF(names);
        co->co_names = names;
        Py_INCREF(varnames);
        co->co_varnames = varnames;
        Py_INCREF(freevars);
        co->co_freevars = freevars;
        Py_INCREF(cellvars);
        co->co_cellvars = cellvars;
        Py_INCREF(filename);
        co->co_filename = filename;
        Py_INCREF(name);
        co->co_name = name;
        co->co_firstlineno = firstlineno;
        Py_INCREF(lnotab);
        co->co_lnotab = lnotab;
        co->co_zombieframe = NULL;
        co->co_weakreflist = NULL;
    }
    return co;
}
