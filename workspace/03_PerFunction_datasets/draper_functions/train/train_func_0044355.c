Perl_custom_op_xop(pTHX_ const OP *o)
{
    SV *keysv;
    HE *he = NULL;
    XOP *xop;

    static const XOP xop_null = { 0, 0, 0, 0, 0 };

    PERL_ARGS_ASSERT_CUSTOM_OP_XOP;
    assert(o->op_type == OP_CUSTOM);


    keysv = sv_2mortal(newSViv(PTR2IV(o->op_ppaddr)));

    if (PL_custom_ops)
	he = hv_fetch_ent(PL_custom_ops, keysv, 0, 0);


    if (!he && PL_custom_op_names &&
	(he = hv_fetch_ent(PL_custom_op_names, keysv, 0, 0))
    ) {
	const char *pv;
	STRLEN l;


	Newxz(xop, 1, XOP);
	pv = SvPV(HeVAL(he), l);
	XopENTRY_set(xop, xop_name, savepvn(pv, l));
	if (PL_custom_op_descs &&
	    (he = hv_fetch_ent(PL_custom_op_descs, keysv, 0, 0))
	) {
	    pv = SvPV(HeVAL(he), l);
	    XopENTRY_set(xop, xop_desc, savepvn(pv, l));
	}
	Perl_custom_op_register(aTHX_ o->op_ppaddr, xop);
	return xop;
    }

    if (!he) return &xop_null;

    xop = INT2PTR(XOP *, SvIV(HeVAL(he)));
    return xop;
}
