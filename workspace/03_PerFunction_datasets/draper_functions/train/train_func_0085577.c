SpectrumDocument ():
	gcu::Document (NULL),
	Printable (),
	m_XAxisInvertBtn (NULL),
	m_Empty (true)
{
	m_View = new SpectrumView (this);
	x = y = NULL;
	X = Y = R = I = integral = Rt = It = Rp = -1;
	npoints = 0;
	maxx = maxy = minx = miny = go_nan;
	firstx = lastx = deltax = firsty = go_nan;
	freq = offset = refpoint = go_nan;
	gtk_page_setup_set_orientation (GetPageSetup (), GTK_PAGE_ORIENTATION_LANDSCAPE);
	SetScaleType (GCU_PRINT_SCALE_AUTO);
	SetHorizFit (true);
	SetVertFit (true);
	m_IntegralVisible = false;
}
