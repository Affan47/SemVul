memory_richcompare(PyObject *v, PyObject *w, int op)
{
    Py_buffer vv, ww;
    int equal = 0;
    PyObject *res;

    vv.obj = NULL;
    ww.obj = NULL;
    if (op != Py_EQ && op != Py_NE)
        goto _notimpl;
    if (PyObject_GetBuffer(v, &vv, PyBUF_CONTIG_RO) == -1) {
        PyErr_Clear();
        goto _notimpl;
    }
    if (PyObject_GetBuffer(w, &ww, PyBUF_CONTIG_RO) == -1) {
        PyErr_Clear();
        goto _notimpl;
    }

    if (vv.itemsize != ww.itemsize || vv.len != ww.len)
        goto _end;

    equal = !memcmp(vv.buf, ww.buf, vv.len);

_end:
    PyBuffer_Release(&vv);
    PyBuffer_Release(&ww);
    if ((equal && op == Py_EQ) || (!equal && op == Py_NE))
        res = Py_True;
    else
        res = Py_False;
    Py_INCREF(res);
    return res;

_notimpl:
    PyBuffer_Release(&vv);
    PyBuffer_Release(&ww);
    Py_INCREF(Py_NotImplemented);
    return Py_NotImplemented;
}
