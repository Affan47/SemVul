Perl_ck_match(pTHX_ OP *o)
{
    dVAR;

    PERL_ARGS_ASSERT_CK_MATCH;

    if (o->op_type != OP_QR && PL_compcv) {
	const PADOFFSET offset = pad_findmy_pvs("$_", 0);
	if (offset != NOT_IN_PAD && !(PAD_COMPNAME_FLAGS_isOUR(offset))) {
	    o->op_targ = offset;
	    o->op_private |= OPpTARGET_MY;
	}
    }
    if (o->op_type == OP_MATCH || o->op_type == OP_QR)
	o->op_private |= OPpRUNTIME;
    return o;
}
