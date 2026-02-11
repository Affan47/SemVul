symtable_warn(struct symtable *st, char *msg, int lineno)
{
    PyObject *message = PyUnicode_FromString(msg);
    if (message == NULL)
        return 0;
    if (PyErr_WarnExplicitObject(PyExc_SyntaxWarning, message, st->st_filename,
                                 lineno, NULL, NULL) < 0)     {
        Py_DECREF(message);
        if (PyErr_ExceptionMatches(PyExc_SyntaxWarning)) {
            PyErr_SetString(PyExc_SyntaxError, msg);
            PyErr_SyntaxLocationObject(st->st_filename, st->st_cur->ste_lineno,
                                       st->st_cur->ste_col_offset);
        }
        return 0;
    }
    Py_DECREF(message);
    return 1;
}
