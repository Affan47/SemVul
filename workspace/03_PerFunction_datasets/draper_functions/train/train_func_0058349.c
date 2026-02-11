slice_richcompare(PyObject *v, PyObject *w, int op)
{
    PyObject *t1;
    PyObject *t2;
    PyObject *res;

    if (!PySlice_Check(v) || !PySlice_Check(w))
        Py_RETURN_NOTIMPLEMENTED;

    if (v == w) {


        switch (op) {
        case Py_EQ:
        case Py_LE:
        case Py_GE:
            res = Py_True;
            break;
        default:
            res = Py_False;
            break;
        }
        Py_INCREF(res);
        return res;
    }

    t1 = PyTuple_New(3);
    if (t1 == NULL)
        return NULL;
    t2 = PyTuple_New(3);
    if (t2 == NULL) {
        Py_DECREF(t1);
        return NULL;
    }

    PyTuple_SET_ITEM(t1, 0, ((PySliceObject *)v)->start);
    PyTuple_SET_ITEM(t1, 1, ((PySliceObject *)v)->stop);
    PyTuple_SET_ITEM(t1, 2, ((PySliceObject *)v)->step);
    PyTuple_SET_ITEM(t2, 0, ((PySliceObject *)w)->start);
    PyTuple_SET_ITEM(t2, 1, ((PySliceObject *)w)->stop);
    PyTuple_SET_ITEM(t2, 2, ((PySliceObject *)w)->step);

    res = PyObject_RichCompare(t1, t2, op);

    PyTuple_SET_ITEM(t1, 0, NULL);
    PyTuple_SET_ITEM(t1, 1, NULL);
    PyTuple_SET_ITEM(t1, 2, NULL);
    PyTuple_SET_ITEM(t2, 0, NULL);
    PyTuple_SET_ITEM(t2, 1, NULL);
    PyTuple_SET_ITEM(t2, 2, NULL);

    Py_DECREF(t1);
    Py_DECREF(t2);

    return res;
}
