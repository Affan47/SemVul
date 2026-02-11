dph_vpos_get(const DirPane *dp)
{
	GtkAdjustment	*adj;

	if((adj = gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(dp->scwin))) != NULL)
		return adj->value;
	return -1.0f;
}
