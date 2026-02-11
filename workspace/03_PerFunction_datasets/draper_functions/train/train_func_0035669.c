deque_ass_item(dequeobject *deque, Py_ssize_t i, PyObject *v)
{
    PyObject *old_value;
    block *b;
    Py_ssize_t n, len=Py_SIZE(deque), halflen=(len+1)>>1, index=i;

    if (i < 0 || i >= len) {
        PyErr_SetString(PyExc_IndexError,
                        "deque index out of range");
        return -1;
    }
    if (v == NULL)
        return deque_del_item(deque, i);

    i += deque->leftindex;
    n = i / BLOCKLEN;
    i %= BLOCKLEN;
    if (index <= halflen) {
        b = deque->leftblock;
        while (n--)
            b = b->rightlink;
    } else {
        n = (deque->leftindex + len - 1) / BLOCKLEN - n;
        b = deque->rightblock;
        while (n--)
            b = b->leftlink;
    }
    Py_INCREF(v);
    old_value = b->data[i];
    b->data[i] = v;
    Py_DECREF(old_value);
    return 0;
}
