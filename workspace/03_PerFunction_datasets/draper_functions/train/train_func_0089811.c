convert_binop(PyObject *v, PyObject *w, PyLongObject **a, PyLongObject **b) {
    if (PyLong_Check(v)) {
        *a = (PyLongObject *) v;
        Py_INCREF(v);
    }
    else if (PyInt_Check(v)) {
        *a = (PyLongObject *) PyLong_FromLong(PyInt_AS_LONG(v));
    }
    else {
        return 0;
    }
    if (PyLong_Check(w)) {
        *b = (PyLongObject *) w;
        Py_INCREF(w);
    }
    else if (PyInt_Check(w)) {
        *b = (PyLongObject *) PyLong_FromLong(PyInt_AS_LONG(w));
    }
    else {
        Py_DECREF(*a);
        return 0;
    }
    return 1;
}
