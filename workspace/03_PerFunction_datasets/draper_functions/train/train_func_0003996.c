prt_level(int row, int col)
{
	char tmp[32];

	strnfmt(tmp, sizeof(tmp), "%6d", p_ptr->lev);

	if (p_ptr->lev >= p_ptr->max_lev)
	{
		put_str("LEVEL ", row, col);
		c_put_str(TERM_L_GREEN, tmp, row, col + 6);
	}
	else
	{
		put_str("Level ", row, col);
		c_put_str(TERM_YELLOW, tmp, row, col + 6);
	}
}
