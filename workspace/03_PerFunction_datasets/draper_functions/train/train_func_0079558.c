load_counted_tuple(Unpicklerobject *self, int len)
{
    PyObject *tup = PyTuple_New(len);

    if (tup == NULL)
        return -1;

    while (--len >= 0) {
        PyObject *element;

        PDATA_POP(self->stack, element);
        if (element == NULL)
            return -1;
        PyTuple_SET_ITEM(tup, len, element);
    }
    PDATA_PUSH(self->stack, tup, -1);
    return 0;
}
