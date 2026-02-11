S_dopoptoloop(pTHX_ I32 startingblock)
{
    dVAR;
    I32 i;
    for (i = startingblock; i >= 0; i--) {
	const PERL_CONTEXT * const cx = &cxstack[i];
	switch (CxTYPE(cx)) {
	case CXt_SUBST:
	case CXt_SUB:
	case CXt_FORMAT:
	case CXt_EVAL:
	case CXt_NULL:

	    Perl_ck_warner(aTHX_ packWARN(WARN_EXITING), "Exiting %s via %s",
			   context_name[CxTYPE(cx)], OP_NAME(PL_op));
	    if ((CxTYPE(cx)) == CXt_NULL)
		return -1;
	    break;
	case CXt_LOOP_LAZYIV:
	case CXt_LOOP_LAZYSV:
	case CXt_LOOP_FOR:
	case CXt_LOOP_PLAIN:
	    DEBUG_l( Perl_deb(aTHX_ "(dopoptoloop(): found loop at cx=%ld)\n", (long)i));
	    return i;
	}
    }
    return i;
}
