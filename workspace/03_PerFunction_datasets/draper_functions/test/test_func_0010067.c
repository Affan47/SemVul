py_tracemalloc_get_traces(PyObject *self, PyObject *obj)
{
    get_traces_t get_traces;
    int err;

    get_traces.traces = NULL;
    get_traces.tracebacks = NULL;
    get_traces.list = PyList_New(0);
    if (get_traces.list == NULL)
        goto error;

    if (!tracemalloc_config.tracing)
        return get_traces.list;


    get_traces.tracebacks = hashtable_new(sizeof(PyObject *),
                                          _Py_hashtable_hash_ptr,
                                          _Py_hashtable_compare_direct);
    if (get_traces.tracebacks == NULL) {
        PyErr_NoMemory();
        goto error;
    }

    TABLES_LOCK();
    get_traces.traces = _Py_hashtable_copy(tracemalloc_traces);
    TABLES_UNLOCK();

    if (get_traces.traces == NULL) {
        PyErr_NoMemory();
        goto error;
    }

    set_reentrant(1);
    err = _Py_hashtable_foreach(get_traces.traces,
                                tracemalloc_get_traces_fill, &get_traces);
    set_reentrant(0);
    if (err)
        goto error;

    goto finally;

error:
    Py_CLEAR(get_traces.list);

finally:
    if (get_traces.tracebacks != NULL) {
        _Py_hashtable_foreach(get_traces.tracebacks,
                         tracemalloc_pyobject_decref_cb, NULL);
        _Py_hashtable_destroy(get_traces.tracebacks);
    }
    if (get_traces.traces != NULL)
        _Py_hashtable_destroy(get_traces.traces);

    return get_traces.list;
}
