draw_margin_footer (UnitInfo *uinfo)
{
	double x1, x2, y2;
	double outside = uinfo->pi->scale *
		uinfo->state->margins.bottom.value;
	double inside = uinfo->pi->scale * uinfo->value;

	x1 = uinfo->bound_x1;
	x2 = uinfo->bound_x2;
	y2 = uinfo->bound_y2;

	if (inside < 1.0)
		inside = 1.0;
	y2 -= outside + inside ;
	move_line (uinfo->line, x1, y2, x2, y2);
}
