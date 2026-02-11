parse_looplimits(
    var_t *var, var_parse_t *ctx,
    const char *begin, const char *end,
    int *start, int *step, int *stop, int *open_stop)
{
    const char *p;
    int rc;
    int failed;


    p = begin;


    if (p == end)
        return VAR_OK;


    if (*p != var->syntax.delim_open)
        return VAR_OK;
    p++;


    failed = 0;
    rc = parse_numexp(var, ctx, p, end, start, &failed);
    if (rc == VAR_ERR_INVALID_CHAR_IN_INDEX_SPEC)
        *start = 0;
    else if (rc < 0)
        return (var_rc_t)rc;
    else
        p += rc;
    if (failed)
        return VAR_ERR_UNDEFINED_VARIABLE;


    if (*p != ',')
        return VAR_ERR_INVALID_CHAR_IN_LOOP_LIMITS;
    p++;


    failed = 0;
    rc = parse_numexp(var, ctx, p, end, step, &failed);
    if (rc == VAR_ERR_INVALID_CHAR_IN_INDEX_SPEC)
        *step = 1;
    else if (rc < 0)
        return (var_rc_t)rc;
    else
        p += rc;
    if (failed)
        return VAR_ERR_UNDEFINED_VARIABLE;


    if (*p != ',') {

        if (*p != var->syntax.delim_close)
            return VAR_ERR_INVALID_CHAR_IN_LOOP_LIMITS;
        p++;


        *stop = *step;
        *step = 1;


        if (rc > 0)
            *open_stop = 0;
        else
            *open_stop = 1;
        return (var_rc_t)(p - begin);
    }
    p++;


    failed = 0;
    rc = parse_numexp(var, ctx, p, end, stop, &failed);
    if (rc == VAR_ERR_INVALID_CHAR_IN_INDEX_SPEC) {
        *stop = 0;
        *open_stop = 1;
    }
    else if (rc < 0)
        return (var_rc_t)rc;
    else {
        *open_stop = 0;
        p += rc;
    }
    if (failed)
        return VAR_ERR_UNDEFINED_VARIABLE;


    if (*p != var->syntax.delim_close)
        return VAR_ERR_INVALID_CHAR_IN_LOOP_LIMITS;
    p++;


    return (var_rc_t)(p - begin);
}
