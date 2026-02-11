func_regexp_flag(struct state *state, int nargs) {
    ensure_arity(2, 2);
    int nocase = 0;
    struct value *f = pop_value(state);

    if (STREQ("i", f->string))
        nocase = 1;
    else
        STATE_ERROR(state, PATHX_EREGEXPFLAG);

    func_regexp_or_glob(state, 0, nocase);
}
