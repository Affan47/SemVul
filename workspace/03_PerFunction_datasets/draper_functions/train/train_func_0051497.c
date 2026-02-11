getFont() const
{


	CursorSlice const & sl = innerTextSlice();
	Text const & text = *sl.text();
	Paragraph const & par = text.getPar(sl.pit());


	pos_type pos = sl.pos();
	if (pos > 0 && boundary())
		--pos;


	if (pos > 0) {
		TextMetrics const & tm = bv().textMetrics(&text);
		if (pos == sl.lastpos()
			|| (par.isSeparator(pos)
			&& !tm.isRTLBoundary(sl.pit(), pos)))
			--pos;
	}


	Font font = par.getFont(buffer()->params(), pos,
		text.outerFont(sl.pit()));

	return font;
}
