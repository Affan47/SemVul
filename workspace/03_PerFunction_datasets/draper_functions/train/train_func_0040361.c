new_symbol_expr(const char *symbol, struct expr *arg)
{
    struct sym_entry e[1];
    struct sym_entry *se;
    int pos;

    e->symbol = symbol;
    pos = vec_find(s_sym_table, sym_entry_cmp, e);
    if(pos > -1)
    {

        LOG(LOG_ERROR, ("not allowed to redefine symbol %s\n", symbol));
        exit(1);
    }
    if(pos == -1)
    {

        LOG(LOG_ERROR, ("new_symbol_expr: vec_find() internal error\n"));
        exit(1);
    }
    e->expr = arg;

    se = vec_insert(s_sym_table, -(pos + 2), e);
    LOG(LOG_DEBUG, ("creating symdef: "));
    dump_sym_entry(LOG_DEBUG, se);
}
