ts_get_quoted_token(cst_tokenstream *ts,
					 char quote,
					 char escape)
{


    int l, p;


    ts->charclass[(unsigned int)quote] |= TS_CHARCLASS_QUOTE;
    ts->charclass[(unsigned int)escape] |= TS_CHARCLASS_QUOTE;


    get_token_sub_part(ts,TS_CHARCLASS_WHITESPACE,
		       &ts->whitespace,
		       &ts->ws_max);
    ts->token_pos = ts->file_pos - 1;

    if (ts->current_char == quote)
    {
	ts_getc(ts);
	l=0;
        for (p=0; ((ts->current_char != TS_EOF) &&
                   (ts->current_char != quote));
             p++)
        {
            if (p >= ts->token_max)
                extend_buffer(&ts->token,&ts->token_max);
            ts->token[p] = ts->current_char;
            ts_getc(ts);
            if (ts->current_char == escape)
            {
                ts_get(ts);
                if (p >= ts->token_max)
                    extend_buffer(&ts->token,&ts->token_max);
                ts->token[p] = ts->current_char;
                ts_get(ts);
            }
        }
        ts->token[p] = '\0';
	ts_getc(ts);
    }
    else
    {

	get_token_sub_part(ts,TS_CHARCLASS_PREPUNCT,
			   &ts->prepunctuation,
			   &ts->prep_max);

	if (!ts_charclass(ts->current_char,TS_CHARCLASS_SINGLECHAR,ts))
	{
	    if (2 >= ts->token_max) extend_buffer(&ts->token,&ts->token_max);
	    ts->token[0] = ts->current_char;
	    ts->token[1] = '\0';
	    ts_getc(ts);
	}
	else
	    get_token_sub_part_2(ts,
				 TS_CHARCLASS_WHITESPACE,
				 &ts->token,
				 &ts->token_max);


	get_token_postpunctuation(ts);
    }

    return ts->token;
}
