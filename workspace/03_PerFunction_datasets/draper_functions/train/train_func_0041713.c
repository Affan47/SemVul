dec_mpd_qquantize(PyObject *v, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"exp", "rounding", "context", NULL};
    PyObject *w, *context;
    PyObject *a, *b;
    PyObject *result;
    uint32_t status = 0;
    mpd_context_t workctx;
    int round = -1;

    CURRENT_CONTEXT(context);
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O|iO", kwlist,
                                     &w, &round, &context)) {
        return NULL;
    }
    CONTEXT_CHECK_VA(context);

    workctx = *CTX(context);
    if (round >= 0) {
        if (!mpd_qsetround(&workctx, round)) {
            return type_error_ptr(invalid_rounding_err);
        }
    }

    CONVERT_BINOP_RAISE(&a, &b, v, w, context);

    result = dec_alloc();
    if (result == NULL) {
        Py_DECREF(a);
        Py_DECREF(b);
        return NULL;
    }

    mpd_qquantize(MPD(result), MPD(a), MPD(b), &workctx, &status);
    Py_DECREF(a);
    Py_DECREF(b);
    if (dec_addstatus(context, status)) {
        Py_DECREF(result);
        return NULL;
    }

    return result;
}
