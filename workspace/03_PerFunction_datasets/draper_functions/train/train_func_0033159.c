Perl_ck_listiob(pTHX_ OP *o)
{
    OP *kid;

    PERL_ARGS_ASSERT_CK_LISTIOB;

    kid = cLISTOPo->op_first;
    if (!kid) {
	o = force_list(o);
	kid = cLISTOPo->op_first;
    }
    if (kid->op_type == OP_PUSHMARK)
	kid = kid->op_sibling;
    if (kid && o->op_flags & OPf_STACKED)
	kid = kid->op_sibling;
    else if (kid && !kid->op_sibling) {
	if (kid->op_type == OP_CONST && kid->op_private & OPpCONST_BARE
	 && !(kid->op_private & OPpCONST_FOLDED)) {
	    o->op_flags |= OPf_STACKED;
	    kid = newUNOP(OP_RV2GV, OPf_REF, scalar(kid));
	    cLISTOPo->op_first->op_sibling = kid;
	    cLISTOPo->op_last = kid;
	    kid = kid->op_sibling;
	}
    }

    if (!kid)
	op_append_elem(o->op_type, o, newDEFSVOP());

    if (o->op_type == OP_PRTF) return modkids(listkids(o), OP_PRTF);
    return listkids(o);
}
