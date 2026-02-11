_PyDict_NewPresized(Py_ssize_t minused)
{
    PyObject *op = PyDict_New();

    if (minused>5 && op != NULL && dictresize((PyDictObject *)op, minused) == -1) {
        Py_DECREF(op);
        return NULL;
    }
    return op;
}
