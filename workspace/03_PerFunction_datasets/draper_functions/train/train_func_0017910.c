_parse_constant(PyScannerObject *s, char *constant, Py_ssize_t idx, Py_ssize_t *next_idx_ptr) {


    PyObject *cstr;
    PyObject *rval;

    cstr = PyUnicode_InternFromString(constant);
    if (cstr == NULL)
        return NULL;


    rval = PyObject_CallFunctionObjArgs(s->parse_constant, cstr, NULL);
    idx += PyUnicode_GET_LENGTH(cstr);
    Py_DECREF(cstr);
    *next_idx_ptr = idx;
    return rval;
}
