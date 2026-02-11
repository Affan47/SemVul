PyFF_FreeSF(SplineFont *sf) {
    Py_XDECREF( (PyObject *) (sf->python_persistent));
    Py_XDECREF( (PyObject *) (sf->python_temporary));
}
