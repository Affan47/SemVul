PyCodec_KnownEncoding(const char *encoding)
{
    PyObject *codecs;

    codecs = _PyCodec_Lookup(encoding);
    if (!codecs) {
        PyErr_Clear();
        return 0;
    }
    else {
        Py_DECREF(codecs);
        return 1;
    }
}
