_wrap_g_uri_list_extract_uris(PyObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "uri_list", NULL };
    char *uri_list;
    char **uris, **tmp;
    int i = 0, j;
    PyObject *ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"s:uri_list_extract_uris", kwlist, &uri_list))
        return NULL;

    uris = (char **)g_uri_list_extract_uris(uri_list);
    if (!uris)
        return PyTuple_New(0);

    tmp = uris;
    while (*tmp)
        tmp++, i++;

    ret = PyTuple_New(i);
    for (j = 0; j < i; j++)
        PyTuple_SetItem(ret, j, PyString_FromString(uris[j]));

    return ret;
}
