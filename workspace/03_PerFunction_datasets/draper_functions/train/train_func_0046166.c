ctx_mpd_to_eng(PyObject *context, PyObject *v)
{
    PyObject *result;
    PyObject *a;
    mpd_ssize_t size;
    char *s;

    CONVERT_OP_RAISE(&a, v, context);

    size = mpd_to_eng_size(&s, MPD(a), CtxCaps(context));
    Py_DECREF(a);
    if (size < 0) {
        PyErr_NoMemory();
        return NULL;
    }

    result = unicode_fromascii(s, size);
    mpd_free(s);

    return result;
}
