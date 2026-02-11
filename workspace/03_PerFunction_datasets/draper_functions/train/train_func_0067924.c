prt_study(int row, int col)
{
	char *text;
	int attr = TERM_WHITE;


	if (p_ptr->new_spells)
	{


		if (!player_can_study_book())
			attr = TERM_L_DARK;


		text = format("Study (%d)", p_ptr->new_spells);
		c_put_str(attr, text, row, col);
		return strlen(text) + 1;
	}

	return 0;
}
