time_get_clock_info(PyObject *self, PyObject *args)
{
    char *name;
    PyObject *obj;
    _Py_clock_info_t info;
    PyObject *result;

    if (!PyArg_ParseTuple(args, "s:get_clock_info", &name))
        return NULL;

#ifdef Py_DEBUG
    info.implementation = NULL;
    info.monotonic = -1;
    info.adjusted = -1;
    info.resolution = -1.0;
#else
    info.implementation = "";
    info.monotonic = 0;
    info.adjusted = 0;
    info.resolution = 1.0;
#endif

    if (strcmp(name, "time") == 0)
        obj = floattime(&info);
#ifdef PYCLOCK
    else if (strcmp(name, "clock") == 0)
        obj = pyclock(&info);
#endif
#ifdef PYMONOTONIC
    else if (strcmp(name, "monotonic") == 0)
        obj = pymonotonic(&info);
#endif
    else if (strcmp(name, "perf_counter") == 0)
        obj = perf_counter(&info);
    else if (strcmp(name, "process_time") == 0)
        obj = py_process_time(&info);
    else {
        PyErr_SetString(PyExc_ValueError, "unknown clock");
        return NULL;
    }
    if (obj == NULL)
        return NULL;
    Py_DECREF(obj);

    result = PyStructSequence_New(&ClockInfoType);
    if (result == NULL)
        return NULL;

    assert(info.implementation != NULL);
    obj = PyUnicode_FromString(info.implementation);
    if (obj == NULL)
        goto error;
    PyStructSequence_SET_ITEM(result, 0, obj);

    assert(info.monotonic != -1);
    obj = PyBool_FromLong(info.monotonic);
    if (obj == NULL)
        goto error;
    PyStructSequence_SET_ITEM(result, 1, obj);

    assert(info.adjusted != -1);
    obj = PyBool_FromLong(info.adjusted);
    if (obj == NULL)
        goto error;
    PyStructSequence_SET_ITEM(result, 2, obj);

    assert(info.resolution > 0.0);
    assert(info.resolution <= 1.0);
    obj = PyFloat_FromDouble(info.resolution);
    if (obj == NULL)
        goto error;
    PyStructSequence_SET_ITEM(result, 3, obj);

    return result;

error:
    Py_DECREF(result);
    return NULL;
}
