vt_ctrl_DCH(struct cpssp *cpssp, unsigned int num)
{
	int i;

	if (num == 0) {
		num = 1;
	}
	if (MAX_COLS < (cpssp->ts.col + num)) {
		num = MAX_COLS - cpssp->ts.col;
		TRACE("DCH: deleting only %d char(s).\n", num);
	}
	i = MAX_COLS - cpssp->ts.col - num;
	if (0 < i) {

		memmove(&cpssp->videobuffer[cpssp->ts.row][cpssp->ts.col],
				&cpssp->videobuffer[cpssp->ts.row][cpssp->ts.col + num],
				i * sizeof(struct vb_char));
	}

	vt_erase_in_line(cpssp, cpssp->ts.row, cpssp->ts.col + i, MAX_COLS);
}
