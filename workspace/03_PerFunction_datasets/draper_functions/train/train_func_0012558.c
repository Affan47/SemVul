_PyGen_FetchStopIterationValue(PyObject **pvalue) {
    PyObject *et, *ev, *tb;
    PyObject *value = NULL;

    if (PyErr_ExceptionMatches(PyExc_StopIteration)) {
        PyErr_Fetch(&et, &ev, &tb);
        Py_XDECREF(et);
        Py_XDECREF(tb);
        if (ev) {
            value = ((PyStopIterationObject *)ev)->value;
            Py_INCREF(value);
            Py_DECREF(ev);
        }
    } else if (PyErr_Occurred()) {
        return -1;
    }
    if (value == NULL) {
        value = Py_None;
        Py_INCREF(value);
    }
    *pvalue = value;
    return 0;
}
