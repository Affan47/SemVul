_PyOS_ascii_strtod(const char *nptr, char **endptr)
{
    double result;
    _Py_SET_53BIT_PRECISION_HEADER;

    assert(nptr != NULL);


    errno = 0;

    _Py_SET_53BIT_PRECISION_START;
    result = _Py_dg_strtod(nptr, endptr);
    _Py_SET_53BIT_PRECISION_END;

    if (*endptr == nptr)

        result = _Py_parse_inf_or_nan(nptr, endptr);

    return result;

}
