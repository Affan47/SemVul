pattern_match(PatternObject *self, PyObject *args, PyObject *kwargs)
{
    static char *_keywords[] = {"string", "pos", "endpos", "pattern", NULL};
    PyObject *string = NULL;
    Py_ssize_t pos = 0;
    Py_ssize_t endpos = PY_SSIZE_T_MAX;
    PyObject *pattern = NULL;
    SRE_STATE state;
    Py_ssize_t status;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,
        "|Onn$O:match", _keywords,
        &string, &pos, &endpos, &pattern))
        return NULL;
    string = fix_string_param(string, pattern, "pattern");
    if (!string)
        return NULL;
    string = state_init(&state, (PatternObject *)self, string, pos, endpos);
    if (!string)
        return NULL;

    state.ptr = state.start;

    TRACE(("|%p|%p|MATCH\n", PatternObject_GetCode(self), state.ptr));

    status = sre_match(&state, PatternObject_GetCode(self), 0);

    TRACE(("|%p|%p|END\n", PatternObject_GetCode(self), state.ptr));
    if (PyErr_Occurred())
        return NULL;

    state_fini(&state);

    return (PyObject *)pattern_new_match(self, &state, status);
}
