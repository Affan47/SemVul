tracemalloc_add_trace(void *ptr, size_t size)
{
    traceback_t *traceback;
    trace_t trace;
    int res;

#ifdef WITH_THREAD
    assert(PyGILState_Check());
#endif

    traceback = traceback_new();
    if (traceback == NULL)
        return -1;

    trace.size = size;
    trace.traceback = traceback;

    res = _Py_HASHTABLE_SET(tracemalloc_traces, ptr, trace);
    if (res == 0) {
        assert(tracemalloc_traced_memory <= PY_SIZE_MAX - size);
        tracemalloc_traced_memory += size;
        if (tracemalloc_traced_memory > tracemalloc_peak_traced_memory)
            tracemalloc_peak_traced_memory = tracemalloc_traced_memory;
    }

    return res;
}
