idxGlue(idx_type idx)
{
	col_type c = col(idx);
	if (c + 1 == ncols()) {
		if (row(idx) + 1 != nrows()) {
			for (col_type cc = 0; cc < ncols(); ++cc)
				cell(idx).append(cell(idx + cc + 1));
			delRow(row(idx) + 1);
		}
	} else {
		cell(idx).append(cell(idx + 1));
		for (col_type cc = c + 2; cc < ncols(); ++cc)
			cell(idx - c + cc - 1) = cell(idx - c + cc);
		cell(idx - c + ncols() - 1).clear();
	}
}
