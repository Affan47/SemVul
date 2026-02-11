yy_get_previous_state (yyscan_t yyscanner)
{
	register yy_state_type yy_current_state;
	register char *yy_cp;
    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;

	yy_current_state = yyg->yy_start;

	for ( yy_cp = yyg->yytext_ptr + YY_MORE_ADJ; yy_cp < yyg->yy_c_buf_p; ++yy_cp )
		{
		if ( *yy_cp )
			{
			yy_current_state = yy_nxt[yy_current_state][YY_SC_TO_UI(*yy_cp)];
			}
		else
			yy_current_state = yy_NUL_trans[yy_current_state];
		if ( yy_accept[yy_current_state] )
			{
			yyg->yy_last_accepting_state = yy_current_state;
			yyg->yy_last_accepting_cpos = yy_cp;
			}
		}

	return yy_current_state;
}
