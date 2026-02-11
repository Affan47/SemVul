AuParser_search_add_regex(AuParser *self, PyObject *args)
{
    const char* regexp;
    int result;

    if (!PyArg_ParseTuple(args, "s", &regexp)) return NULL;
    PARSER_CHECK;
    result = ausearch_add_regex(self->au, regexp);
    if (result == 0) Py_RETURN_NONE;
    PyErr_SetFromErrno(PyExc_EnvironmentError);
    return NULL;
}
