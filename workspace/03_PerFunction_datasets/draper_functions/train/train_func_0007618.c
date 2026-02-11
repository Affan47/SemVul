ExposePreeditThis(GtkWidget *widget, GdkEventExpose *ose) {
	try {
		gchar *str;
		gint cursor_pos;
		PangoAttrList *attrs;

		gtk_im_context_get_preedit_string(im_context, &str, &attrs, &cursor_pos);
		PangoLayout *layout = gtk_widget_create_pango_layout(PWidget(wText), str);
		pango_layout_set_attributes(layout, attrs);

		cairo_t *context = gdk_cairo_create(reinterpret_cast<GdkDrawable *>(WindowFromWidget(widget)));
		cairo_move_to(context, 0, 0);
		pango_cairo_show_layout(context, layout);
		cairo_destroy(context);
		g_free(str);
		pango_attr_list_unref(attrs);
		g_object_unref(layout);
	} catch (...) {
		errorStatus = SC_STATUS_FAILURE;
	}
	return TRUE;
}
