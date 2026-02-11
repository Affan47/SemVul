makecode(struct compiler *c, struct assembler *a)
{
    PyObject *tmp;
    PyCodeObject *co = NULL;
    PyObject *consts = NULL;
    PyObject *names = NULL;
    PyObject *varnames = NULL;
    PyObject *filename = NULL;
    PyObject *name = NULL;
    PyObject *freevars = NULL;
    PyObject *cellvars = NULL;
    PyObject *bytecode = NULL;
    int nlocals, flags;

    tmp = dict_keys_inorder(c->u->u_consts, 0);
    if (!tmp)
        goto error;
    consts = PySequence_List(tmp);
    Py_DECREF(tmp);

    names = dict_keys_inorder(c->u->u_names, 0);
    varnames = dict_keys_inorder(c->u->u_varnames, 0);
    if (!consts || !names || !varnames)
        goto error;

    cellvars = dict_keys_inorder(c->u->u_cellvars, 0);
    if (!cellvars)
        goto error;
    freevars = dict_keys_inorder(c->u->u_freevars, PyTuple_Size(cellvars));
    if (!freevars)
        goto error;
    filename = PyString_FromString(c->c_filename);
    if (!filename)
        goto error;

    nlocals = PyDict_Size(c->u->u_varnames);
    flags = compute_code_flags(c);
    if (flags < 0)
        goto error;

    bytecode = PyCode_Optimize(a->a_bytecode, consts, names, a->a_lnotab);
    if (!bytecode)
        goto error;

    tmp = PyList_AsTuple(consts);
    if (!tmp)
        goto error;
    Py_DECREF(consts);
    consts = tmp;

    co = PyCode_New(c->u->u_argcount, nlocals, stackdepth(c), flags,
                    bytecode, consts, names, varnames,
                    freevars, cellvars,
                    filename, c->u->u_name,
                    c->u->u_firstlineno,
                    a->a_lnotab);
 error:
    Py_XDECREF(consts);
    Py_XDECREF(names);
    Py_XDECREF(varnames);
    Py_XDECREF(filename);
    Py_XDECREF(name);
    Py_XDECREF(freevars);
    Py_XDECREF(cellvars);
    Py_XDECREF(bytecode);
    return co;
}
