cb_style_extent (GnmStyle *style,
		 int corner_col, int corner_row, int width, int height,
		 GnmRange const *apply_to, gpointer user)
{
	GnmRange *res = user;
	if (gnm_style_visible_in_blank (style)) {
		int tmp;


		width = MIN (width, apply_to->end.col - corner_col + 1);
		height = MIN (height, apply_to->end.row - corner_row + 1);

		tmp = corner_col+width-1;
		if (res->end.col < tmp)
			res->end.col = tmp;
		if (res->start.col > corner_col)
			res->start.col = corner_col;

		tmp = corner_row+height-1;
		if (res->end.row < tmp)
			res->end.row = tmp;
		if (res->start.row > corner_row)
			res->start.row = corner_row;
	}
}
