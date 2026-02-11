metrics(MetricsInfo & mi, Dimension & dim) const
{
	Dimension dim0;
	Dimension dim1;
	Dimension dim2;
	cell(0).metrics(mi, dim0);
	ScriptChanger dummy(mi.base);
	if (nargs() > 1)
		cell(1).metrics(mi, dim1);
	if (nargs() > 2)
		cell(2).metrics(mi, dim2);

	dim.wid = 0;
	BufferView & bv = *mi.base.bv;

	Dimension dimup;
	Dimension dimdown;
	if (hasUp())
		dimup = up().dimension(bv);
	if (hasDown())
		dimdown = down().dimension(bv);

	if (hasLimits()) {
		dim.wid = nwid(bv);
		if (hasUp())
			dim.wid = max(dim.wid, dimup.width());
		if (hasDown())
			dim.wid = max(dim.wid, dimdown.width());
	} else {
		if (hasUp())
			dim.wid = max(dim.wid, nker(mi.base.bv) + dimup.width());
		if (hasDown())
			dim.wid = max(dim.wid, dimdown.width());
		dim.wid += nwid(bv);
	}
	int na = nasc(bv);
	if (hasUp()) {
		int asc = dy1(bv) + dimup.ascent();
		dim.asc = max(na, asc);
	} else
		dim.asc = na;
	int nd = ndes(bv);
	if (hasDown()) {
		int des = dy0(bv) + dimdown.descent();
		dim.des = max(nd, des);
	} else
		dim.des = nd;
	metricsMarkers(dim);
}
