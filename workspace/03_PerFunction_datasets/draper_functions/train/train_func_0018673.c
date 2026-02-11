showfiles(struct dnode **dn, unsigned nfiles)
{
	unsigned i, ncols, nrows, row, nc;
	unsigned column = 0;
	unsigned nexttab = 0;
	unsigned column_width = 0;

	if (all_fmt & STYLE_LONG) {
		ncols = 1;
	} else {

		for (i = 0; dn[i]; i++) {
			int len = calc_name_len(dn[i]->name);
			if (column_width < len)
				column_width = len;
		}
		column_width += tabstops +
			IF_SELINUX( ((all_fmt & LIST_CONTEXT) ? 33 : 0) + )
				((all_fmt & LIST_INO) ? 8 : 0) +
				((all_fmt & LIST_BLOCKS) ? 5 : 0);
		ncols = (int) (terminal_width / column_width);
	}

	if (ncols > 1) {
		nrows = nfiles / ncols;
		if (nrows * ncols < nfiles)
			nrows++;
	} else {
		nrows = nfiles;
		ncols = 1;
	}

	for (row = 0; row < nrows; row++) {
		for (nc = 0; nc < ncols; nc++) {

			if (all_fmt & DISP_ROWS)
				i = (row * ncols) + nc;
			else
				i = (nc * nrows) + row;
			if (i < nfiles) {
				if (column > 0) {
					nexttab -= column;
					printf("%*s", nexttab, "");
					column += nexttab;
				}
				nexttab = column + column_width;
				column += list_single(dn[i]);
			}
		}
		putchar('\n');
		column = 0;
	}
}
