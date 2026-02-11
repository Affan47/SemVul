vim_regcomp(expr_arg, re_flags)
    char_u	*expr_arg;
    int		re_flags;
{
    regprog_T   *prog = NULL;
    char_u	*expr = expr_arg;

    regexp_engine = p_re;


    if (STRNCMP(expr, "\\%#=", 4) == 0)
    {
	int newengine = expr[4] - '0';

	if (newengine == AUTOMATIC_ENGINE
	    || newengine == BACKTRACKING_ENGINE
	    || newengine == NFA_ENGINE)
	{
	    regexp_engine = expr[4] - '0';
	    expr += 5;
#ifdef DEBUG
	    EMSG3("New regexp mode selected (%d): %s", regexp_engine,
						    regname[newengine]);
#endif
	}
	else
	{
	    EMSG(_("E864: \\%#= can only be followed by 0, 1, or 2. The automatic engine will be used "));
	    regexp_engine = AUTOMATIC_ENGINE;
	}
    }
#ifdef DEBUG
    bt_regengine.expr = expr;
    nfa_regengine.expr = expr;
#endif


    if (regexp_engine != BACKTRACKING_ENGINE)
        prog = nfa_regengine.regcomp(expr, re_flags);
    else
	prog = bt_regengine.regcomp(expr, re_flags);

    if (prog == NULL)
    {
#ifdef BT_REGEXP_DEBUG_LOG
	if (regexp_engine != BACKTRACKING_ENGINE)
	{
	    FILE *f;
	    f = fopen(BT_REGEXP_DEBUG_LOG_NAME, "a");
	    if (f)
	    {
		fprintf(f, "Syntax error in \"%s\"\n", expr);
		fclose(f);
	    }
	    else
		EMSG2("(NFA) Could not open \"%s\" to write !!!",
                        BT_REGEXP_DEBUG_LOG_NAME);
	}
#endif


    }

    return prog;
}
