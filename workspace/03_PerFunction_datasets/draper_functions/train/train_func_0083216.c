compiler_visit_annotations(struct compiler *c, arguments_ty args,
                           expr_ty returns)
{


    static identifier return_str;
    PyObject *names;
    int len;
    names = PyList_New(0);
    if (!names)
        return -1;

    if (compiler_visit_argannotations(c, args->args, names))
        goto error;
    if (args->varargannotation &&
        compiler_visit_argannotation(c, args->vararg,
                                     args->varargannotation, names))
        goto error;
    if (compiler_visit_argannotations(c, args->kwonlyargs, names))
        goto error;
    if (args->kwargannotation &&
        compiler_visit_argannotation(c, args->kwarg,
                                     args->kwargannotation, names))
        goto error;

    if (!return_str) {
        return_str = PyUnicode_InternFromString("return");
        if (!return_str)
            goto error;
    }
    if (compiler_visit_argannotation(c, return_str, returns, names)) {
        goto error;
    }

    len = PyList_GET_SIZE(names);
    if (len > 65534) {

        PyErr_SetString(PyExc_SyntaxError,
                        "too many annotations");
        goto error;
    }
    if (len) {

        PyObject *elt;
        int i;
        PyObject *s = PyTuple_New(len);
        if (!s)
            goto error;
        for (i = 0; i < len; i++) {
            elt = PyList_GET_ITEM(names, i);
            Py_INCREF(elt);
            PyTuple_SET_ITEM(s, i, elt);
        }
        ADDOP_O(c, LOAD_CONST, s, consts);
        Py_DECREF(s);
        len++;
    }
    Py_DECREF(names);
    return len;

error:
    Py_DECREF(names);
    return -1;
}
