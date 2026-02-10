Perl_ck_subr(pTHX_ OP *o)
{
    OP *aop, *cvop;
    CV *cv;
    GV *namegv;

    PERL_ARGS_ASSERT_CK_SUBR;

    aop = cUNOPx(o)->op_first;
    if (!aop->op_sibling)
	aop = cUNOPx(aop)->op_first;
    aop = aop->op_sibling;
    for (cvop = aop; cvop->op_sibling; cvop = cvop->op_sibling) ;
    cv = rv2cv_op_cv(cvop, RV2CVOPCV_MARK_EARLY);
    namegv = cv ? (GV*)rv2cv_op_cv(cvop, RV2CVOPCV_RETURN_NAME_GV) : NULL;

    o->op_private &= ~1;
    o->op_private |= OPpENTERSUB_HASTARG;
    o->op_private |= (PL_hints & HINT_STRICT_REFS);
    if (PERLDB_SUB && PL_curstash != PL_debstash)
	o->op_private |= OPpENTERSUB_DB;
    if (cvop->op_type == OP_RV2CV) {
	o->op_private |= (cvop->op_private & OPpENTERSUB_AMPER);
	op_null(cvop);
    } else if (cvop->op_type == OP_METHOD || cvop->op_type == OP_METHOD_NAMED) {
	if (aop->op_type == OP_CONST)
	    aop->op_private &= ~OPpCONST_STRICT;
	else if (aop->op_type == OP_LIST) {
	    OP * const sib = ((UNOP*)aop)->op_first->op_sibling;
	    if (sib && sib->op_type == OP_CONST)
		sib->op_private &= ~OPpCONST_STRICT;
	}
    }

    if (!cv) {
	return ck_entersub_args_list(o);
    } else {
	Perl_call_checker ckfun;
	SV *ckobj;
	cv_get_call_checker(cv, &ckfun, &ckobj);
	if (!namegv) {


	    HEK * const hek = CvNAME_HEK(cv);


	    if (!hek) return ck_entersub_args_list(o);;
	    namegv = (GV *)sv_newmortal();
	    gv_init_pvn(namegv, PL_curstash, HEK_KEY(hek), HEK_LEN(hek),
			SVf_UTF8 * !!HEK_UTF8(hek));
	}
	return ckfun(aTHX_ o, namegv, ckobj);
    }
}
