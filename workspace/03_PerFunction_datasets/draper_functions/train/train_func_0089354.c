S_parse_recdescent(pTHX_ int gramtype, I32 fakeeof)
{
    SAVEI32(PL_lex_brackets);
    if (PL_lex_brackets > 100)
	Renew(PL_lex_brackstack, PL_lex_brackets + 10, char);
    PL_lex_brackstack[PL_lex_brackets++] = XFAKEEOF;
    SAVEI32(PL_lex_allbrackets);
    PL_lex_allbrackets = 0;
    SAVEI8(PL_lex_fakeeof);
    PL_lex_fakeeof = (U8)fakeeof;
    if(yyparse(gramtype) && !PL_parser->error_count)
	qerror(Perl_mess(aTHX_ "Parse error"));
}
