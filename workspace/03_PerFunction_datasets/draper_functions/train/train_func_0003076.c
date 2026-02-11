pattern_match(PatternObject* self, PyObject* args, PyObject* kw)
{
    SRE_STATE state;
    int status;

    PyObject* string;
    Py_ssize_t start = 0;
    Py_ssize_t end = PY_SSIZE_T_MAX;
    static char* kwlist[] = { "pattern", "pos", "endpos", NULL };
    if (!PyArg_ParseTupleAndKeywords(args, kw, "O|nn:match", kwlist,
                                     &string, &start, &end))
        return NULL;

    string = state_init(&state, self, string, start, end);
    if (!string)
        return NULL;

    state.ptr = state.start;

    TRACE(("|%p|%p|MATCH\n", PatternObject_GetCode(self), state.ptr));

    if (state.logical_charsize == 1) {
        status = sre_match(&state, PatternObject_GetCode(self));
    } else {
        status = sre_umatch(&state, PatternObject_GetCode(self));
    }

    TRACE(("|%p|%p|END\n", PatternObject_GetCode(self), state.ptr));
    if (PyErr_Occurred())
        return NULL;

    state_fini(&state);

    return pattern_new_match(self, &state, status);
}
