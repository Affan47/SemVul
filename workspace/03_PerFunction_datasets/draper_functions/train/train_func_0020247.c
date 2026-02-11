drawWithMargin(PainterInfo & pi, int x, int y,
	int lmargin, int rmargin) const
{
	Dimension const dim = dimension(*pi.base.bv);
	BufferView const & bv = *pi.base.bv;

	for (idx_type idx = 0; idx < nargs(); ++idx)
		cell(idx).draw(pi, x + lmargin + cellXOffset(bv, idx),
			y + cellYOffset(idx));

	for (row_type row = 0; row <= nrows(); ++row)
		for (unsigned int i = 0; i < rowinfo_[row].lines_; ++i) {
			int yy = y + rowinfo_[row].offset_ - rowinfo_[row].ascent_
				- i * hlinesep() - hlinesep()/2 - rowsep()/2;
			pi.pain.line(x + lmargin + 1, yy,
				     x + dim.width() - rmargin - 1, yy,
				     Color_foreground);
		}

	for (col_type col = 0; col <= ncols(); ++col)
		for (unsigned int i = 0; i < colinfo_[col].lines_; ++i) {
			int xx = x + lmargin + colinfo_[col].offset_
				- i * vlinesep() - vlinesep()/2 - colsep()/2;
			pi.pain.line(xx, y - dim.ascent() + 1,
				     xx, y + dim.descent() - 1,
				     Color_foreground);
		}
	drawMarkers2(pi, x, y);
}
