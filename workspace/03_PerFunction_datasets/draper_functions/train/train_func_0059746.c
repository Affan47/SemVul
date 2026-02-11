yyinput()
{
	int c;

	*(yy_c_buf_p) = (yy_hold_char);

	if ( *(yy_c_buf_p) == YY_END_OF_BUFFER_CHAR )
		{


		if ( (yy_c_buf_p) < &YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[(yy_n_chars)] )

			*(yy_c_buf_p) = '\0';

		else
			{
			yy_size_t offset = (yy_c_buf_p) - (yytext_ptr);
			++(yy_c_buf_p);

			switch ( yy_get_next_buffer(  ) )
				{
				case EOB_ACT_LAST_MATCH:


					yyrestart( yyin );


				case EOB_ACT_END_OF_FILE:
					{
					if ( yywrap(  ) )
						return EOF;

					if ( ! (yy_did_buffer_switch_on_eof) )
						YY_NEW_FILE;
#ifdef __cplusplus
					return yyinput();
#else
					return input();
#endif
					}

				case EOB_ACT_CONTINUE_SCAN:
					(yy_c_buf_p) = (yytext_ptr) + offset;
					break;
				}
			}
		}

	c = *(unsigned char *) (yy_c_buf_p);
	*(yy_c_buf_p) = '\0';
	(yy_hold_char) = *++(yy_c_buf_p);

	return c;
}
