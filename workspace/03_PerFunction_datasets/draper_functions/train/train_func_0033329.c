_validate(PatternObject *self)
{
    if (!_validate_outer(self->code, self->code+self->codesize, self->groups))
    {
        PyErr_SetString(PyExc_RuntimeError, "invalid SRE code");
        return 0;
    }
    else
        VTRACE(("Success!\n"));
    return 1;
}
