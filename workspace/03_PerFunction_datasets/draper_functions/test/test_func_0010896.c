yajl_gen_array_close(yajl_gen g)
{
    ENSURE_VALID_STATE;
    if (g->pretty) g->print(g->ctx, "\n", 1);
    (g->depth)--;
    APPENDED_ATOM;
    INSERT_WHITESPACE;
    g->print(g->ctx, "]", 1);
    FINAL_NEWLINE;
    return yajl_gen_status_ok;
}
