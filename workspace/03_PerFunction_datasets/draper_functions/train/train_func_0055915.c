yy_get_next_buffer()
	{
	register char *dest = yy_current_buffer->yy_ch_buf;
	register char *source = yytext_ptr - 1;
	register int number_to_move, i;
	int ret_val;

	if ( yy_c_buf_p > &yy_current_buffer->yy_ch_buf[yy_n_chars + 1] )
		YY_FATAL_ERROR(
		"fatal flex scanner internal error--end of buffer missed" );

	if ( yy_current_buffer->yy_fill_buffer == 0 )
		{
		if ( yy_c_buf_p - yytext_ptr - YY_MORE_ADJ == 1 )
			{


			return EOB_ACT_END_OF_FILE;
			}

		else
			{


			return EOB_ACT_LAST_MATCH;
			}
		}


	number_to_move = yy_c_buf_p - yytext_ptr;

	for ( i = 0; i < number_to_move; ++i )
		*(dest++) = *(source++);

	if ( yy_current_buffer->yy_buffer_status == YY_BUFFER_EOF_PENDING )


		yy_n_chars = 0;

	else
		{
		int num_to_read =
			yy_current_buffer->yy_buf_size - number_to_move - 1;

		while ( num_to_read <= 0 )
			{
#ifdef YY_USES_REJECT
			YY_FATAL_ERROR(
"input buffer overflow, can't enlarge buffer because scanner uses REJECT" );
#else


			YY_BUFFER_STATE b = yy_current_buffer;

			int yy_c_buf_p_offset = yy_c_buf_p - b->yy_ch_buf;

			b->yy_buf_size *= 2;
			b->yy_ch_buf = (char *)
				yy_flex_realloc( (void *) b->yy_ch_buf,
						 b->yy_buf_size );

			if ( ! b->yy_ch_buf )
				YY_FATAL_ERROR(
				"fatal error - scanner input buffer overflow" );

			yy_c_buf_p = &b->yy_ch_buf[yy_c_buf_p_offset];

			num_to_read = yy_current_buffer->yy_buf_size -
						number_to_move - 1;
#endif
			}

		if ( num_to_read > YY_READ_BUF_SIZE )
			num_to_read = YY_READ_BUF_SIZE;


		YY_INPUT( (&yy_current_buffer->yy_ch_buf[number_to_move]),
			yy_n_chars, num_to_read );
		}

	if ( yy_n_chars == 0 )
		{
		if ( number_to_move - YY_MORE_ADJ == 1 )
			{
			ret_val = EOB_ACT_END_OF_FILE;
			yyrestart( yyin );
			}

		else
			{
			ret_val = EOB_ACT_LAST_MATCH;
			yy_current_buffer->yy_buffer_status =
				YY_BUFFER_EOF_PENDING;
			}
		}

	else
		ret_val = EOB_ACT_CONTINUE_SCAN;

	yy_n_chars += number_to_move;
	yy_current_buffer->yy_ch_buf[yy_n_chars] = YY_END_OF_BUFFER_CHAR;
	yy_current_buffer->yy_ch_buf[yy_n_chars + 1] = YY_END_OF_BUFFER_CHAR;


	yytext_ptr = &yy_current_buffer->yy_ch_buf[1];

	return ret_val;
	}
