deque_item(dequeobject *deque, Py_ssize_t i)
{
    block *b;
    PyObject *item;
    Py_ssize_t n, index=i;

    if (i < 0 || i >= deque->len) {
        PyErr_SetString(PyExc_IndexError,
                        "deque index out of range");
        return NULL;
    }

    if (i == 0) {
        i = deque->leftindex;
        b = deque->leftblock;
    } else if (i == deque->len - 1) {
        i = deque->rightindex;
        b = deque->rightblock;
    } else {
        i += deque->leftindex;
        n = i / BLOCKLEN;
        i %= BLOCKLEN;
        if (index < (deque->len >> 1)) {
            b = deque->leftblock;
            while (n--)
                b = b->rightlink;
        } else {
            n = (deque->leftindex + deque->len - 1) / BLOCKLEN - n;
            b = deque->rightblock;
            while (n--)
                b = b->leftlink;
        }
    }
    item = b->data[i];
    Py_INCREF(item);
    return item;
}
