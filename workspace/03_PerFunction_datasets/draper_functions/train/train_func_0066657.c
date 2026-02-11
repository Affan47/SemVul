S_lop(pTHX_ I32 f, int x, char *s)
{
    dVAR;

    PERL_ARGS_ASSERT_LOP;

    pl_yylval.ival = f;
    CLINE;
    PL_expect = x;
    PL_bufptr = s;
    PL_last_lop = PL_oldbufptr;
    PL_last_lop_op = (OPCODE)f;
#ifdef PERL_MAD
    if (PL_lasttoke)
	goto lstop;
#else
    if (PL_nexttoke)
	goto lstop;
#endif
    if (*s == '(')
	return REPORT(FUNC);
    s = PEEKSPACE(s);
    if (*s == '(')
	return REPORT(FUNC);
    else {
	lstop:
	if (!PL_lex_allbrackets && PL_lex_fakeeof > LEX_FAKEEOF_LOWLOGIC)
	    PL_lex_fakeeof = LEX_FAKEEOF_LOWLOGIC;
	return REPORT(LSTOP);
    }
}
