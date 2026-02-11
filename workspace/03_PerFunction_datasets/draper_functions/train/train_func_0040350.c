codec_getincrementalcodec(const char *encoding,
                                    const char *errors,
                                    const char *attrname)
{
    PyObject *codec_info, *ret;

    codec_info = _PyCodec_Lookup(encoding);
    if (codec_info == NULL)
        return NULL;
    ret = codec_makeincrementalcodec(codec_info, errors, attrname);
    Py_DECREF(codec_info);
    return ret;
}
