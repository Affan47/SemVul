yy_try_NUL_trans  (yy_state_type yy_current_state , yyscan_t yyscanner)
{
	register int yy_is_jam;
    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
	register char *yy_cp = yyg->yy_c_buf_p;

	yy_current_state = yy_nxt[yy_current_state*YY_NXT_LOLEN + 1];
	yy_is_jam = (yy_current_state <= 0);

	if ( ! yy_is_jam )
		{
		if ( yy_accept[yy_current_state] )
			{
			yyg->yy_last_accepting_state = yy_current_state;
			yyg->yy_last_accepting_cpos = yy_cp;
			}
		}

	return yy_is_jam ? 0 : yy_current_state;
}
