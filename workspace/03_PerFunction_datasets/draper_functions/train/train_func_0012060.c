S_dopoptolabel(pTHX_ const char *label, STRLEN len, U32 flags)
{
    dVAR;
    I32 i;

    PERL_ARGS_ASSERT_DOPOPTOLABEL;

    for (i = cxstack_ix; i >= 0; i--) {
	const PERL_CONTEXT * const cx = &cxstack[i];
	switch (CxTYPE(cx)) {
	case CXt_SUBST:
	case CXt_SUB:
	case CXt_FORMAT:
	case CXt_EVAL:
	case CXt_NULL:

	    Perl_ck_warner(aTHX_ packWARN(WARN_EXITING), "Exiting %s via %s",
			   context_name[CxTYPE(cx)], OP_NAME(PL_op));
	    if (CxTYPE(cx) == CXt_NULL)
		return -1;
	    break;
	case CXt_LOOP_LAZYIV:
	case CXt_LOOP_LAZYSV:
	case CXt_LOOP_FOR:
	case CXt_LOOP_PLAIN:
	  {
            STRLEN cx_label_len = 0;
            U32 cx_label_flags = 0;
	    const char *cx_label = CxLABEL_len_flags(cx, &cx_label_len, &cx_label_flags);
	    if (!cx_label || !(
                    ( (cx_label_flags & SVf_UTF8) != (flags & SVf_UTF8) ) ?
                        (flags & SVf_UTF8)
                            ? (bytes_cmp_utf8(
                                        (const U8*)cx_label, cx_label_len,
                                        (const U8*)label, len) == 0)
                            : (bytes_cmp_utf8(
                                        (const U8*)label, len,
                                        (const U8*)cx_label, cx_label_len) == 0)
                    : (len == cx_label_len && ((cx_label == label)
                                    || memEQ(cx_label, label, len))) )) {
		DEBUG_l(Perl_deb(aTHX_ "(poptolabel(): skipping label at cx=%ld %s)\n",
			(long)i, cx_label));
		continue;
	    }
	    DEBUG_l( Perl_deb(aTHX_ "(poptolabel(): found label at cx=%ld %s)\n", (long)i, label));
	    return i;
	  }
	}
    }
    return i;
}
