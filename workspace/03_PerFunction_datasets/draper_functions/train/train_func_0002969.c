merge_getmem(MergeState *ms, Py_ssize_t need)
{
    assert(ms != NULL);
    if (need <= ms->alloced)
        return 0;


    merge_freemem(ms);
    if ((size_t)need > PY_SSIZE_T_MAX / sizeof(PyObject*)) {
        PyErr_NoMemory();
        return -1;
    }
    ms->a = (PyObject **)PyMem_Malloc(need * sizeof(PyObject*));
    if (ms->a) {
        ms->alloced = need;
        return 0;
    }
    PyErr_NoMemory();
    merge_freemem(ms);
    return -1;
}
