cpm_dump(PyObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"obj", "file", "protocol", NULL};
    PyObject *ob, *file, *res = NULL;
    Picklerobject *pickler = 0;
    int proto = 0;

    if (!( PyArg_ParseTupleAndKeywords(args, kwds, "OO|i", kwlist,
               &ob, &file, &proto)))
        goto finally;

    if (!( pickler = newPicklerobject(file, proto)))
        goto finally;

    if (dump(pickler, ob) < 0)
        goto finally;

    Py_INCREF(Py_None);
    res = Py_None;

  finally:
    Py_XDECREF(pickler);

    return res;
}
