PyCodec_RegisterError(const char *name, PyObject *error)
{
    PyInterpreterState *interp = PyThreadState_GET()->interp;
    if (interp->codec_search_path == NULL && _PyCodecRegistry_Init())
        return -1;
    if (!PyCallable_Check(error)) {
        PyErr_SetString(PyExc_TypeError, "handler must be callable");
        return -1;
    }
    return PyDict_SetItemString(interp->codec_error_registry,
                                (char *)name, error);
}
