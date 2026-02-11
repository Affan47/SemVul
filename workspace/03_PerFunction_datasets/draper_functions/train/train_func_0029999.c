compress_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    PyObject *seq1, *seq2;
    PyObject *data=NULL, *selectors=NULL;
    compressobject *lz;
    static char *kwargs[] = {"data", "selectors", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "OO:compress", kwargs, &seq1, &seq2))
        return NULL;

    data = PyObject_GetIter(seq1);
    if (data == NULL)
        goto fail;
    selectors = PyObject_GetIter(seq2);
    if (selectors == NULL)
        goto fail;


    lz = (compressobject *)type->tp_alloc(type, 0);
    if (lz == NULL)
        goto fail;
    lz->data = data;
    lz->selectors = selectors;
    return (PyObject *)lz;

fail:
    Py_XDECREF(data);
    Py_XDECREF(selectors);
    return NULL;
}
