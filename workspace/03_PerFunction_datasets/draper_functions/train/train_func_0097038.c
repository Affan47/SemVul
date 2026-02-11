ast_error(const node *n, const char *errstr)
{
    PyObject *u = Py_BuildValue("zii", errstr, LINENO(n), n->n_col_offset);
    if (!u)
        return 0;
    PyErr_SetObject(PyExc_SyntaxError, u);
    Py_DECREF(u);
    return 0;
}
