draw(PainterInfo & pi, int x, int y) const
{
	Dimension const dim = dimension(*pi.base.bv);
	Dimension const & dim0 = cell(0).dimension(*pi.base.bv);
	Dimension const & dim1 = cell(1).dimension(*pi.base.bv);

	docstring const bra = kind_ == BRACE ? from_ascii("{") :
		kind_ == BRACK ? from_ascii("[") : from_ascii("(");
	docstring const ket = kind_ == BRACE ? from_ascii("}") :
		kind_ == BRACK ? from_ascii("]") : from_ascii(")");

	int m = x + dim.width() / 2;


	if (kind_ == DBINOM) {
		StyleChanger dummy(pi.base, LM_ST_DISPLAY);
		cell(0).draw(pi, m - dim0.wid / 2, y - dim0.des - 3 - 5);
		cell(1).draw(pi, m - dim1.wid / 2, y + dim1.asc + 3 - 5);
	} else if (kind_ == TBINOM) {
		StyleChanger dummy(pi.base, LM_ST_SCRIPT);
		cell(0).draw(pi, m - dim0.wid / 2, y - dim0.des - 3 - 5);
		cell(1).draw(pi, m - dim1.wid / 2, y + dim1.asc + 3 - 5);
	} else {
		FracChanger dummy2(pi.base);
		cell(0).draw(pi, m - dim0.wid / 2, y - dim0.des - 3 - 5);
		cell(1).draw(pi, m - dim1.wid / 2, y + dim1.asc + 3 - 5);
	}

	mathed_draw_deco(pi, x, y - dim.ascent(), dw(dim.height()),
		dim.height(), bra);
	mathed_draw_deco(pi, x + dim.width() - dw(dim.height()),
		y - dim.ascent(), dw(dim.height()), dim.height(), ket);
	drawMarkers2(pi, x, y);
}
