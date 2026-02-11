GMT_flush_symbol_piece (double *x, double *y, double z, GMT_LONG *n, struct GMT_PEN *p, struct GMT_FILL *f, GMT_LONG outline, GMT_LONG *flush) {
	GMT_LONG draw_outline;

	draw_outline = (outline && p->rgb[0] != -1) ? TRUE : FALSE;
	if (draw_outline) GMT_setpen (p);
	if (project_info.three_D) GMT_2Dz_to_3D (x, y, z, (GMT_LONG)*n);
	GMT_fill (x, y, (GMT_LONG)*n, f, draw_outline);
	*flush = FALSE;
	*n = 0;
}
