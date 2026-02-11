traceback_new(void)
{
    traceback_t *traceback;
    _Py_hashtable_entry_t *entry;

#ifdef WITH_THREAD
    assert(PyGILState_Check());
#endif


    traceback = tracemalloc_traceback;
    traceback->nframe = 0;
    traceback_get_frames(traceback);
    if (traceback->nframe == 0)
        return &tracemalloc_empty_traceback;
    traceback->hash = traceback_hash(traceback);


    entry = _Py_hashtable_get_entry(tracemalloc_tracebacks, traceback);
    if (entry != NULL) {
        traceback = (traceback_t *)entry->key;
    }
    else {
        traceback_t *copy;
        size_t traceback_size;

        traceback_size = TRACEBACK_SIZE(traceback->nframe);

        copy = raw_malloc(traceback_size);
        if (copy == NULL) {
#ifdef TRACE_DEBUG
            tracemalloc_error("failed to intern the traceback: malloc failed");
#endif
            return NULL;
        }
        memcpy(copy, traceback, traceback_size);

        if (_Py_hashtable_set(tracemalloc_tracebacks, copy, NULL, 0) < 0) {
            raw_free(copy);
#ifdef TRACE_DEBUG
            tracemalloc_error("failed to intern the traceback: putdata failed");
#endif
            return NULL;
        }
        traceback = copy;
    }
    return traceback;
}
