_siftup(PyListObject *heap, Py_ssize_t pos)
{
    Py_ssize_t startpos, endpos, childpos, rightpos;
    int cmp;
    PyObject *newitem, *tmp, *olditem;
    Py_ssize_t size;

    assert(PyList_Check(heap));
    size = PyList_GET_SIZE(heap);
    endpos = size;
    startpos = pos;
    if (pos >= endpos) {
        PyErr_SetString(PyExc_IndexError, "index out of range");
        return -1;
    }
    newitem = PyList_GET_ITEM(heap, pos);
    Py_INCREF(newitem);


    childpos = 2*pos + 1;
    while (childpos < endpos) {

        rightpos = childpos + 1;
        if (rightpos < endpos) {
            cmp = PyObject_RichCompareBool(
                PyList_GET_ITEM(heap, childpos),
                PyList_GET_ITEM(heap, rightpos),
                Py_LT);
            if (cmp == -1) {
                Py_DECREF(newitem);
                return -1;
            }
            if (cmp == 0)
                childpos = rightpos;
        }
        if (size != PyList_GET_SIZE(heap)) {
            Py_DECREF(newitem);
            PyErr_SetString(PyExc_RuntimeError,
                            "list changed size during iteration");
            return -1;
        }

        tmp = PyList_GET_ITEM(heap, childpos);
        Py_INCREF(tmp);
        olditem = PyList_GET_ITEM(heap, pos);
        PyList_SET_ITEM(heap, pos, tmp);
        Py_DECREF(olditem);
        pos = childpos;
        childpos = 2*pos + 1;
        if (size != PyList_GET_SIZE(heap)) {
            PyErr_SetString(PyExc_RuntimeError,
                            "list changed size during iteration");
            return -1;
        }
    }


    Py_DECREF(PyList_GET_ITEM(heap, pos));
    PyList_SET_ITEM(heap, pos, newitem);
    return _siftdown(heap, startpos, pos);
}
