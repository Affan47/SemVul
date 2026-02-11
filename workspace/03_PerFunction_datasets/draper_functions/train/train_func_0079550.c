load_args(PyObject ***pp_stack, int na)
{
    PyObject *args = PyTuple_New(na);
    PyObject *w;

    if (args == NULL)
        return NULL;
    while (--na >= 0) {
        w = EXT_POP(*pp_stack);
        PyTuple_SET_ITEM(args, na, w);
    }
    return args;
}
