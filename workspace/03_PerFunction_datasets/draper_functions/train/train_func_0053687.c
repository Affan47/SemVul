prt_depth(int row, int col)
{
	char depths[32];

	if (!p_ptr->depth)
	{
		my_strcpy(depths, "Town", sizeof(depths));
	}
	else
	{
		strnfmt(depths, sizeof(depths), "%d' (L%d)",
		        p_ptr->depth * 50, p_ptr->depth);
	}


	put_str(format("%-13s", depths), row, col);
}
