tracemalloc_deinit(void)
{
    if (tracemalloc_config.initialized != TRACEMALLOC_INITIALIZED)
        return;
    tracemalloc_config.initialized = TRACEMALLOC_FINALIZED;

    tracemalloc_stop();


    _Py_hashtable_destroy(tracemalloc_traces);
    _Py_hashtable_destroy(tracemalloc_tracebacks);
    _Py_hashtable_destroy(tracemalloc_filenames);

#if defined(WITH_THREAD) && defined(TRACE_RAW_MALLOC)
    if (tables_lock != NULL) {
        PyThread_free_lock(tables_lock);
        tables_lock = NULL;
    }
#endif

#ifdef REENTRANT_THREADLOCAL
    PyThread_delete_key(tracemalloc_reentrant_key);
#endif

    Py_XDECREF(unknown_filename);
}
