dequeiter_next(dequeiterobject *it)
{
    PyObject *item;

    if (it->deque->state != it->state) {
        it->counter = 0;
        PyErr_SetString(PyExc_RuntimeError,
                        "deque mutated during iteration");
        return NULL;
    }
    if (it->counter == 0)
        return NULL;
    assert (!(it->b == it->deque->rightblock &&
              it->index > it->deque->rightindex));

    item = it->b->data[it->index];
    it->index++;
    it->counter--;
    if (it->index == BLOCKLEN && it->counter > 0) {
        assert (it->b->rightlink != NULL);
        it->b = it->b->rightlink;
        it->index = 0;
    }
    Py_INCREF(item);
    return item;
}
