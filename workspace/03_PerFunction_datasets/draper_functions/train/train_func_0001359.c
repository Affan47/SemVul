list_select(GtkWidget *w, gint row, gint column, GdkEventButton *eb, gpointer data)
{
	struct gui_object *obj;
	GdkPixmap *pm = NULL;
	GdkBitmap *bm = NULL;
	char *text;
	guint8 spacing;
	obj = gtk_clist_get_row_data(GTK_CLIST(w), row);
	if (!eb)
		return;
	current = obj;
	if (eb->button == 1) {
		gtk_clist_get_pixtext(GTK_CLIST(w), row, 0, &text, &spacing, &pm, &bm);
		gtk_drag_set_default_icon(gdk_colormap_get_system(), pm, bm, 10, 10);
		gastman_object_select(obj->pvt);
	} else if (eb->button == 3) {
		bbutton = eb->button;
		btime = eb->time;
		gastman_right_click(obj->pvt);
	}
}
