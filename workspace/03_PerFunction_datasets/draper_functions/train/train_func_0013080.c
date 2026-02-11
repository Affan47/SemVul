paint_focus(GB_DRAW *d, GtkStyle *style, int x, int y, int w, int h, GtkStateType state, const char *kind)
{
	gtk_paint_focus(style, DR(d)->drawable(),
		state,
		get_area(d), DR(d)->widget(), kind,
		x, y, w, h);
	if (DR(d)->mask())
		gtk_paint_focus(style, DR(d)->mask(),
			state,
			get_area(d), DR(d)->widget(), kind,
			x, y, w, h);
}
