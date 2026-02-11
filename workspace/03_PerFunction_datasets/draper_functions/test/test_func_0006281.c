getargs_keyword_only(PyObject *self, PyObject *args, PyObject *kwargs)
{
    static char *keywords[] = {"required", "optional", "keyword_only", NULL};
    int required = -1;
    int optional = -1;
    int keyword_only = -1;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i|i$i", keywords,
                                     &required, &optional, &keyword_only))
        return NULL;
    return Py_BuildValue("iii", required, optional, keyword_only);
}
