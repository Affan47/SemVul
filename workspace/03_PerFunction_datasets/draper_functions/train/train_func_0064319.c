dec_repr(PyObject *dec)
{
    PyObject *res, *context;
    char *cp;

    CURRENT_CONTEXT(context);
    cp = mpd_to_sci(MPD(dec), CtxCaps(context));
    if (cp == NULL) {
        PyErr_NoMemory();
        return NULL;
    }

    res = PyUnicode_FromFormat("Decimal('%s')", cp);
    mpd_free(cp);
    return res;
}
