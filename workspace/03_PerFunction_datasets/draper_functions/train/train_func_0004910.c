nsmallest(PyObject *self, PyObject *args)
{
    PyObject *heap=NULL, *elem, *iterable, *los, *it, *oldelem;
    Py_ssize_t i, n;
    int cmp;

    if (!PyArg_ParseTuple(args, "nO:nsmallest", &n, &iterable))
        return NULL;

    it = PyObject_GetIter(iterable);
    if (it == NULL)
        return NULL;

    heap = PyList_New(0);
    if (heap == NULL)
        goto fail;

    for (i=0 ; i<n ; i++ ){
        elem = PyIter_Next(it);
        if (elem == NULL) {
            if (PyErr_Occurred())
                goto fail;
            else
                goto sortit;
        }
        if (PyList_Append(heap, elem) == -1) {
            Py_DECREF(elem);
            goto fail;
        }
        Py_DECREF(elem);
    }
    n = PyList_GET_SIZE(heap);
    if (n == 0)
        goto sortit;

    for (i=n/2-1 ; i>=0 ; i--)
        if(_siftupmax((PyListObject *)heap, i) == -1)
            goto fail;

    los = PyList_GET_ITEM(heap, 0);
    while (1) {
        elem = PyIter_Next(it);
        if (elem == NULL) {
            if (PyErr_Occurred())
                goto fail;
            else
                goto sortit;
        }
        cmp = PyObject_RichCompareBool(elem, los, Py_LT);
        if (cmp == -1) {
            Py_DECREF(elem);
            goto fail;
        }
        if (cmp == 0) {
            Py_DECREF(elem);
            continue;
        }

        oldelem = PyList_GET_ITEM(heap, 0);
        PyList_SET_ITEM(heap, 0, elem);
        Py_DECREF(oldelem);
        if (_siftupmax((PyListObject *)heap, 0) == -1)
            goto fail;
        los = PyList_GET_ITEM(heap, 0);
    }

sortit:
    if (PyList_Sort(heap) == -1)
        goto fail;
    Py_DECREF(it);
    return heap;

fail:
    Py_DECREF(it);
    Py_XDECREF(heap);
    return NULL;
}
