test_thread_state(PyObject *self, PyObject *args)
{
    PyObject *fn;
    int success = 1;

    if (!PyArg_ParseTuple(args, "O:test_thread_state", &fn))
        return NULL;

    if (!PyCallable_Check(fn)) {
        PyErr_Format(PyExc_TypeError, "'%s' object is not callable",
            fn->ob_type->tp_name);
        return NULL;
    }


    PyEval_InitThreads();
    thread_done = PyThread_allocate_lock();
    if (thread_done == NULL)
        return PyErr_NoMemory();
    PyThread_acquire_lock(thread_done, 1);


    PyThread_start_new_thread(_make_call_from_thread, fn);

    success &= _make_call(fn);

    Py_BEGIN_ALLOW_THREADS
    success &= _make_call(fn);
    PyThread_acquire_lock(thread_done, 1);
    Py_END_ALLOW_THREADS


    Py_BEGIN_ALLOW_THREADS
    PyThread_start_new_thread(_make_call_from_thread, fn);
    success &= _make_call(fn);
    PyThread_acquire_lock(thread_done, 1);
    Py_END_ALLOW_THREADS


    PyThread_release_lock(thread_done);

    PyThread_free_lock(thread_done);
    if (!success)
        return NULL;
    Py_RETURN_NONE;
}
