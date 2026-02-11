load_counted_tuple(UnpicklerObject *self, int len)
{
    PyObject *tuple;

    tuple = PyTuple_New(len);
    if (tuple == NULL)
        return -1;

    while (--len >= 0) {
        PyObject *item;

        PDATA_POP(self->stack, item);
        if (item == NULL)
            return -1;
        PyTuple_SET_ITEM(tuple, len, item);
    }
    PDATA_PUSH(self->stack, tuple, -1);
    return 0;
}
