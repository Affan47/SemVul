gr_rmoveto_pt(double rx_pt, double ry_pt)
{
	extern FILE    *_grPS;
	if (!_grPathExists)
		warning("IGNORING gr_rmoveto() NOT FOLLOWING gr_moveto()");
	else {
		_grCurrentPoint_x += rx_pt;
		_grCurrentPoint_y += ry_pt;
		if (_grWritePS)
			fprintf(_grPS, PS_rmoveto, rx_pt, ry_pt);
	}
}
