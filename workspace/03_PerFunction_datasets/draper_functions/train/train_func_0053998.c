PyFrame_FastToLocals(PyFrameObject *f)
{

    PyObject *locals, *map;
    PyObject **fast;
    PyObject *error_type, *error_value, *error_traceback;
    PyCodeObject *co;
    Py_ssize_t j;
    int ncells, nfreevars;
    if (f == NULL)
        return;
    locals = f->f_locals;
    if (locals == NULL) {
        locals = f->f_locals = PyDict_New();
        if (locals == NULL) {
            PyErr_Clear();
            return;
        }
    }
    co = f->f_code;
    map = co->co_varnames;
    if (!PyTuple_Check(map))
        return;
    PyErr_Fetch(&error_type, &error_value, &error_traceback);
    fast = f->f_localsplus;
    j = PyTuple_GET_SIZE(map);
    if (j > co->co_nlocals)
        j = co->co_nlocals;
    if (co->co_nlocals)
        map_to_dict(map, j, locals, fast, 0);
    ncells = PyTuple_GET_SIZE(co->co_cellvars);
    nfreevars = PyTuple_GET_SIZE(co->co_freevars);
    if (ncells || nfreevars) {
        map_to_dict(co->co_cellvars, ncells,
                    locals, fast + co->co_nlocals, 1);


        if (co->co_flags & CO_OPTIMIZED) {
            map_to_dict(co->co_freevars, nfreevars,
                        locals, fast + co->co_nlocals + ncells, 1);
        }
    }
    PyErr_Restore(error_type, error_value, error_traceback);
}
