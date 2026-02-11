join_list_unicode(PyObject *lst)
{

    PyObject *sep, *ret;
    sep = PyUnicode_FromStringAndSize("", 0);
    ret = PyUnicode_Join(sep, lst);
    Py_DECREF(sep);
    return ret;
}
