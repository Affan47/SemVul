replace_text(PG_FUNCTION_ARGS)
{
	text	   *src_text = PG_GETARG_TEXT_PP(0);
	text	   *from_sub_text = PG_GETARG_TEXT_PP(1);
	text	   *to_sub_text = PG_GETARG_TEXT_PP(2);
	int			src_text_len;
	int			from_sub_text_len;
	TextPositionState state;
	text	   *ret_text;
	int			start_posn;
	int			curr_posn;
	int			chunk_len;
	char	   *start_ptr;
	StringInfoData str;

	text_position_setup(src_text, from_sub_text, &state);


	src_text_len = state.len1;
	from_sub_text_len = state.len2;


	if (src_text_len < 1 || from_sub_text_len < 1)
	{
		text_position_cleanup(&state);
		PG_RETURN_TEXT_P(src_text);
	}

	start_posn = 1;
	curr_posn = text_position_next(1, &state);


	if (curr_posn == 0)
	{
		text_position_cleanup(&state);
		PG_RETURN_TEXT_P(src_text);
	}


	start_ptr = VARDATA_ANY(src_text);

	initStringInfo(&str);

	do
	{
		CHECK_FOR_INTERRUPTS();


		chunk_len = charlen_to_bytelen(start_ptr, curr_posn - start_posn);
		appendBinaryStringInfo(&str, start_ptr, chunk_len);

		appendStringInfoText(&str, to_sub_text);

		start_posn = curr_posn;
		start_ptr += chunk_len;
		start_posn += from_sub_text_len;
		start_ptr += charlen_to_bytelen(start_ptr, from_sub_text_len);

		curr_posn = text_position_next(start_posn, &state);
	}
	while (curr_posn > 0);


	chunk_len = ((char *) src_text + VARSIZE_ANY(src_text)) - start_ptr;
	appendBinaryStringInfo(&str, start_ptr, chunk_len);

	text_position_cleanup(&state);

	ret_text = PG_STR_GET_TEXT(str.data);
	pfree(str.data);

	PG_RETURN_TEXT_P(ret_text);
}
