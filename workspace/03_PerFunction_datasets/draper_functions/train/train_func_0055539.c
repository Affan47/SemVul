Perl_ck_concat(pTHX_ OP *o)
{
    const OP * const kid = cUNOPo->op_first;

    PERL_ARGS_ASSERT_CK_CONCAT;
    PERL_UNUSED_CONTEXT;

    if (kid->op_type == OP_CONCAT && !(kid->op_private & OPpTARGET_MY) &&
	    !(kUNOP->op_first->op_flags & OPf_MOD))
        o->op_flags |= OPf_STACKED;
    return o;
}
