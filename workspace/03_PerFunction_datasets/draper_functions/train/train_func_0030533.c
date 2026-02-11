jump_percent(percent)
	int percent;
{
	POSITION pos, len;


	if ((len = ch_length()) == NULL_POSITION)
	{
		ierror("Determining length of file", NULL_PARG);
		ch_end_seek();
	}
	if ((len = ch_length()) == NULL_POSITION)
	{
		error("Don't know length of file", NULL_PARG);
		return;
	}
	pos = percent_pos(len, percent);
	if (pos >= len)
		pos = len-1;

	jump_line_loc(pos, jump_sline);
}
