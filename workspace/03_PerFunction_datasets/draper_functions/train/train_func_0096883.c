S_clear_yystack(pTHX_  const yy_parser *parser)
{
    yy_stack_frame *ps     = parser->ps;
    int i = 0;

    if (!parser->stack)
	return;

    YYDPRINTF ((Perl_debug_log, "clearing the parse stack\n"));

    for (i=0; i< parser->yylen; i++) {
	SvREFCNT_dec(ps[-i].compcv);
    }
    ps -= parser->yylen;


    while (ps > parser->stack) {
	LEAVE_SCOPE(ps->savestack_ix);
	if (yy_type_tab[yystos[ps->state]] == toketype_opval
	    && ps->val.opval)
	{
	    if (ps->compcv != PL_compcv) {
		PL_compcv = ps->compcv;
		PAD_SET_CUR_NOSAVE(CvPADLIST(PL_compcv), 1);
	    }
	    YYDPRINTF ((Perl_debug_log, "(freeing op)\n"));
	    op_free(ps->val.opval);
	}
	SvREFCNT_dec(ps->compcv);
	ps--;
    }

    Safefree(parser->stack);
}
