fold_unaryops_on_constants(unsigned char *codestr, PyObject *consts)
{
    PyObject *newconst=NULL, *v;
    Py_ssize_t len_consts;
    int opcode;


    assert(PyList_CheckExact(consts));
    assert(codestr[0] == LOAD_CONST);


    v = PyList_GET_ITEM(consts, GETARG(codestr, 0));
    opcode = codestr[3];
    switch (opcode) {
        case UNARY_NEGATIVE:

            if (PyObject_IsTrue(v) == 1)
                newconst = PyNumber_Negative(v);
            break;
        case UNARY_CONVERT:
            newconst = PyObject_Repr(v);
            break;
        case UNARY_INVERT:
            newconst = PyNumber_Invert(v);
            break;
        default:

            PyErr_Format(PyExc_SystemError,
                 "unexpected unary operation %d on a constant",
                     opcode);
            return 0;
    }
    if (newconst == NULL) {
        PyErr_Clear();
        return 0;
    }


    len_consts = PyList_GET_SIZE(consts);
    if (PyList_Append(consts, newconst)) {
        Py_DECREF(newconst);
        return 0;
    }
    Py_DECREF(newconst);


    codestr[0] = NOP;
    codestr[1] = LOAD_CONST;
    SETARG(codestr, 1, len_consts);
    return 1;
}
