list_repeat(PyListObject *a, Py_ssize_t n)
{
    Py_ssize_t i, j;
    Py_ssize_t size;
    PyListObject *np;
    PyObject **p, **items;
    PyObject *elem;
    if (n < 0)
        n = 0;
    if (n > 0 && Py_SIZE(a) > PY_SSIZE_T_MAX / n)
        return PyErr_NoMemory();
    size = Py_SIZE(a) * n;
    if (size == 0)
        return PyList_New(0);
    np = (PyListObject *) PyList_New(size);
    if (np == NULL)
        return NULL;

    items = np->ob_item;
    if (Py_SIZE(a) == 1) {
        elem = a->ob_item[0];
        for (i = 0; i < n; i++) {
            items[i] = elem;
            Py_INCREF(elem);
        }
        return (PyObject *) np;
    }
    p = np->ob_item;
    items = a->ob_item;
    for (i = 0; i < n; i++) {
        for (j = 0; j < Py_SIZE(a); j++) {
            *p = items[j];
            Py_INCREF(*p);
            p++;
        }
    }
    return (PyObject *) np;
}
