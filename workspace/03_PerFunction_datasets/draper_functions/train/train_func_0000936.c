Perl_ck_sort(pTHX_ OP *o)
{
    dVAR;
    OP *firstkid;
    HV * const hinthv = GvHV(PL_hintgv);

    PERL_ARGS_ASSERT_CK_SORT;

    if (hinthv) {
	    SV ** const svp = hv_fetchs(hinthv, "sort", FALSE);
	    if (svp) {
		const I32 sorthints = (I32)SvIV(*svp);
		if ((sorthints & HINT_SORT_QUICKSORT) != 0)
		    o->op_private |= OPpSORT_QSORT;
		if ((sorthints & HINT_SORT_STABLE) != 0)
		    o->op_private |= OPpSORT_STABLE;
	    }
    }

    if (o->op_flags & OPf_STACKED)
	simplify_sort(o);
    firstkid = cLISTOPo->op_first->op_sibling;
    if (o->op_flags & OPf_STACKED) {
	OP *kid = cUNOPx(firstkid)->op_first;

	if (kid->op_type == OP_SCOPE || kid->op_type == OP_LEAVE) {
	    LINKLIST(kid);
	    if (kid->op_type == OP_LEAVE)
		    op_null(kid);

	    kid->op_next = 0;


	    kid = scalar(firstkid);
	    kid->op_next = kid;
	    o->op_flags |= OPf_SPECIAL;
	}

	firstkid = firstkid->op_sibling;
    }


    list(firstkid);

    return o;
}
