PyType_IsSubtype(PyTypeObject *a, PyTypeObject *b)
{
    PyObject *mro;

    mro = a->tp_mro;
    if (mro != NULL) {


        Py_ssize_t i, n;
        assert(PyTuple_Check(mro));
        n = PyTuple_GET_SIZE(mro);
        for (i = 0; i < n; i++) {
            if (PyTuple_GET_ITEM(mro, i) == (PyObject *)b)
                return 1;
        }
        return 0;
    }
    else {

        do {
            if (a == b)
                return 1;
            a = a->tp_base;
        } while (a != NULL);
        return b == &PyBaseObject_Type;
    }
}
