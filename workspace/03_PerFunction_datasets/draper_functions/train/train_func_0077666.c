yy_get_previous_state (void)


{
	register yy_state_type yy_current_state;
	register char *yy_cp;


	yy_current_state = (yy_start);

	for ( yy_cp = (yytext_ptr) + YY_MORE_ADJ; yy_cp < (yy_c_buf_p); ++yy_cp )
		{

		if ( *yy_cp )
			{
			yy_current_state = yy_nxt[yy_current_state][YY_SC_TO_UI(*yy_cp)];
			}
		else
			yy_current_state = yy_NUL_trans[yy_current_state];
		}

	return yy_current_state;
}
