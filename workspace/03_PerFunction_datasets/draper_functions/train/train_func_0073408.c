Perl_ck_eof(pTHX_ OP *o)
{
    dVAR;

    PERL_ARGS_ASSERT_CK_EOF;

    if (o->op_flags & OPf_KIDS) {
	OP *kid;
	if (cLISTOPo->op_first->op_type == OP_STUB) {
	    OP * const newop
		= newUNOP(o->op_type, OPf_SPECIAL, newGVOP(OP_GV, 0, PL_argvgv));
#ifdef PERL_MAD
	    op_getmad(o,newop,'O');
#else
	    op_free(o);
#endif
	    o = newop;
	}
	o = ck_fun(o);
	kid = cLISTOPo->op_first;
	if (kid->op_type == OP_RV2GV)
	    kid->op_private |= OPpALLOW_FAKE;
    }
    return o;
}
