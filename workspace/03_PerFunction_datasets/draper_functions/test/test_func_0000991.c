handle_boolean (void *ctx, int boolean_value)
{
    yajl_val v;

    v = value_alloc (boolean_value ? yajl_t_true : yajl_t_false);
    if (v == NULL)
        RETURN_ERROR ((context_t *) ctx, STATUS_ABORT, "Out of memory");

    return ((context_add_value (ctx, v) == 0) ? STATUS_CONTINUE : STATUS_ABORT);
}
