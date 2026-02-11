PyObject_Compare(PyObject *v, PyObject *w)
{
    int result;

    if (v == NULL || w == NULL) {
        PyErr_BadInternalCall();
        return -1;
    }
    if (v == w)
        return 0;
    if (Py_EnterRecursiveCall(" in cmp"))
        return -1;
    result = do_cmp(v, w);
    Py_LeaveRecursiveCall();
    return result < 0 ? -1 : result;
}
