prt_dtrap(int row, int col)
{
	byte info = cave_info2[p_ptr->py][p_ptr->px];


	if (info & (CAVE2_DTRAP))
	{

		if (dtrap_edge(p_ptr->py, p_ptr->px))
			c_put_str(TERM_YELLOW, "DTrap", row, col);
		else
			c_put_str(TERM_L_GREEN, "DTrap", row, col);

		return 5;
	}

	return 0;
}
