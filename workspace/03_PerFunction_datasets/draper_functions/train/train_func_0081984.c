indexedvalidate(i_ctx_t *i_ctx_p, ref *space, float *values, int num_comps)
{
    int code;
    ref hival;
    os_ptr op = osp;

    if (num_comps < 1)
        return_error(e_stackunderflow);

    if (!r_has_type(op, t_integer) && !r_has_type(op, t_real))
        return_error(e_typecheck);

    code = array_get(imemory, space, 2, &hival);
    if (code < 0)
        return code;

    if (*values > hival.value.intval)
        *values = (float)hival.value.intval;

    if (*values < 0)
        *values = 0;


    *values = floor(*values);

    return 0;
}
