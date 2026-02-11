dig_restore_line(struct Plus_head *plus, int lineid,
		 int type, struct line_pnts *Points,
		 long offset)
{
    if (lineid < 1 || lineid > plus->n_lines) {
	return -1;
    }

    return add_line(plus, lineid, type, Points, offset);
}
