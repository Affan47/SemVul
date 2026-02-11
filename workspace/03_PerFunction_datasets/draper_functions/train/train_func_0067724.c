pack_single(char *ptr, PyObject *item, const char *fmt, Py_ssize_t itemsize)
{
    PyObject *structobj = NULL, *pack_into = NULL, *args = NULL;
    PyObject *format = NULL, *mview = NULL, *zero = NULL;
    Py_ssize_t i, nmemb;
    int ret = -1;
    PyObject *x;

    if (fmt == NULL) fmt = "B";

    format = PyUnicode_FromString(fmt);
    if (format == NULL)
        goto out;

    structobj = PyObject_CallFunctionObjArgs(Struct, format, NULL);
    if (structobj == NULL)
        goto out;

    nmemb = get_nmemb(structobj);
    assert(nmemb >= 1);

    mview = PyMemoryView_FromMemory(ptr, itemsize, PyBUF_WRITE);
    if (mview == NULL)
        goto out;

    zero = PyLong_FromLong(0);
    if (zero == NULL)
        goto out;

    pack_into = PyObject_GetAttrString(structobj, "pack_into");
    if (pack_into == NULL)
        goto out;

    args = PyTuple_New(2+nmemb);
    if (args == NULL)
        goto out;

    PyTuple_SET_ITEM(args, 0, mview);
    PyTuple_SET_ITEM(args, 1, zero);

    if ((PyBytes_Check(item) || PyLong_Check(item) ||
         PyFloat_Check(item)) && nmemb == 1) {
         PyTuple_SET_ITEM(args, 2, item);
    }
    else if ((PyList_Check(item) || PyTuple_Check(item)) &&
             PySequence_Length(item) == nmemb) {
        for (i = 0; i < nmemb; i++) {
            x = PySequence_Fast_GET_ITEM(item, i);
            PyTuple_SET_ITEM(args, 2+i, x);
        }
    }
    else {
        PyErr_SetString(PyExc_ValueError,
            "mismatch between initializer element and format string");
        goto args_out;
    }

    x = PyObject_CallObject(pack_into, args);
    if (x != NULL) {
        Py_DECREF(x);
        ret = 0;
    }


args_out:
    for (i = 0; i < 2+nmemb; i++)
        Py_XINCREF(PyTuple_GET_ITEM(args, i));
    Py_XDECREF(args);
out:
    Py_XDECREF(pack_into);
    Py_XDECREF(zero);
    Py_XDECREF(mview);
    Py_XDECREF(structobj);
    Py_XDECREF(format);
    return ret;
}
