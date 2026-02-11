dropwhile_next(dropwhileobject *lz)
{
    PyObject *item, *good;
    PyObject *it = lz->it;
    long ok;
    PyObject *(*iternext)(PyObject *);

    iternext = *Py_TYPE(it)->tp_iternext;
    for (;;) {
        item = iternext(it);
        if (item == NULL)
            return NULL;
        if (lz->start == 1)
            return item;

        good = PyObject_CallFunctionObjArgs(lz->func, item, NULL);
        if (good == NULL) {
            Py_DECREF(item);
            return NULL;
        }
        ok = PyObject_IsTrue(good);
        Py_DECREF(good);
        if (ok == 0) {
            lz->start = 1;
            return item;
        }
        Py_DECREF(item);
        if (ok < 0)
            return NULL;
    }
}
