zop_init(i_ctx_t *i_ctx_p)
{
    const op_def *const *tptr;
    int code;


    const op_def *def;

    for (tptr = op_defs_all; *tptr != 0; tptr++) {
        for (def = *tptr; def->oname != 0; def++)
            DO_NOTHING;
        if (def->proc != 0) {
            code = def->proc(i_ctx_p);
            if (code < 0) {
                lprintf2("op_init proc 0x%lx returned error %d!\n",
                         (ulong)def->proc, code);
                return code;
            }
        }
    }


    {
        ref vcr, vpr, vpf, vre, vrd;

        make_const_string(&vcr, a_readonly | avm_foreign,
                          strlen(gs_copyright), (const byte *)gs_copyright);
        make_const_string(&vpr, a_readonly | avm_foreign,
                          strlen(gs_product), (const byte *)gs_product);
        make_const_string(&vpf, a_readonly | avm_foreign,
                          strlen(gs_productfamily),
                          (const byte *)gs_productfamily);
        make_int(&vre, gs_revision);
        make_int(&vrd, gs_revisiondate);
        if ((code = initial_enter_name("copyright", &vcr)) < 0 ||
            (code = initial_enter_name("product", &vpr)) < 0 ||
            (code = initial_enter_name("productfamily", &vpf)) < 0 ||
            (code = initial_enter_name("revision", &vre)) < 0 ||
            (code = initial_enter_name("revisiondate", &vrd)) < 0)
            return code;
    }

    return 0;
}
