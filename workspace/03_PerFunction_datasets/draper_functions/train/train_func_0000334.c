elementtree_clear(PyObject *m)
{
    elementtreestate *st = ET_STATE(m);
    Py_CLEAR(st->parseerror_obj);
    Py_CLEAR(st->deepcopy_obj);
    Py_CLEAR(st->elementpath_obj);
    return 0;
}
