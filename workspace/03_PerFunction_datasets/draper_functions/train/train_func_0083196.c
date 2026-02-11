PyFrame_FastToLocalsWithError(PyFrameObject *f)
{

    PyObject *locals, *map;
    PyObject **fast;
    PyCodeObject *co;
    Py_ssize_t j;
    Py_ssize_t ncells, nfreevars;

    if (f == NULL) {
        PyErr_BadInternalCall();
        return -1;
    }
    locals = f->f_locals;
    if (locals == NULL) {
        locals = f->f_locals = PyDict_New();
        if (locals == NULL)
            return -1;
    }
    co = f->f_code;
    map = co->co_varnames;
    if (!PyTuple_Check(map)) {
        PyErr_Format(PyExc_SystemError,
                     "co_varnames must be a tuple, not %s",
                     Py_TYPE(map)->tp_name);
        return -1;
    }
    fast = f->f_localsplus;
    j = PyTuple_GET_SIZE(map);
    if (j > co->co_nlocals)
        j = co->co_nlocals;
    if (co->co_nlocals) {
        if (map_to_dict(map, j, locals, fast, 0) < 0)
            return -1;
    }
    ncells = PyTuple_GET_SIZE(co->co_cellvars);
    nfreevars = PyTuple_GET_SIZE(co->co_freevars);
    if (ncells || nfreevars) {
        if (map_to_dict(co->co_cellvars, ncells,
                        locals, fast + co->co_nlocals, 1))
            return -1;


        if (co->co_flags & CO_OPTIMIZED) {
            if (map_to_dict(co->co_freevars, nfreevars,
                            locals, fast + co->co_nlocals + ncells, 1) < 0)
                return -1;
        }
    }
    return 0;
}
