read_list(ScmPort *port, ScmChar closer, ScmReadContext *ctx)
{
    int has_ref;
    int line = -1;
    ScmObj r;

    if (ctx->flags & SCM_READ_SOURCE_INFO) line = Scm_PortLine(port);

    r = read_list_int(port, closer, ctx, &has_ref, line);

    if (SCM_PAIRP(r) && (ctx->flags & SCM_READ_SOURCE_INFO) && line >= 0) {


        r = Scm_ExtendedCons(SCM_CAR(r), SCM_CDR(r));
        Scm_PairAttrSet(SCM_PAIR(r), SCM_SYM_SOURCE_INFO,
                        SCM_LIST2(Scm_PortName(port), SCM_MAKE_INT(line)));
    }

    if (has_ref) ref_push(ctx, r, SCM_FALSE);
    return r;
}
