PyCodec_LookupError(const char *name)
{
    PyObject *handler = NULL;

    PyInterpreterState *interp = PyThreadState_GET()->interp;
    if (interp->codec_search_path == NULL && _PyCodecRegistry_Init())
        return NULL;

    if (name==NULL)
        name = "strict";
    handler = PyDict_GetItemString(interp->codec_error_registry, name);
    if (!handler)
        PyErr_Format(PyExc_LookupError, "unknown error handler name '%.400s'", name);
    else
        Py_INCREF(handler);
    return handler;
}
