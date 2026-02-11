missing_arguments(PyCodeObject *co, int missing, int defcount,
                  PyObject **fastlocals)
{
    int i, j = 0;
    int start, end;
    int positional = defcount != -1;
    const char *kind = positional ? "positional" : "keyword-only";
    PyObject *missing_names;


    missing_names = PyList_New(missing);
    if (missing_names == NULL)
        return;
    if (positional) {
        start = 0;
        end = co->co_argcount - defcount;
    }
    else {
        start = co->co_argcount;
        end = start + co->co_kwonlyargcount;
    }
    for (i = start; i < end; i++) {
        if (GETLOCAL(i) == NULL) {
            PyObject *raw = PyTuple_GET_ITEM(co->co_varnames, i);
            PyObject *name = PyObject_Repr(raw);
            if (name == NULL) {
                Py_DECREF(missing_names);
                return;
            }
            PyList_SET_ITEM(missing_names, j++, name);
        }
    }
    assert(j == missing);
    format_missing(kind, co, missing_names);
    Py_DECREF(missing_names);
}
