dragText(gControl *source, char *text, char *format)
{
	GtkTargetList *list;
	GdkDragContext *ct;


	setDropText(text);

	list = gtk_target_list_new (NULL, 0);
	if (format)
		gtk_target_list_add(list, gdk_atom_intern(format, false), 0, 0);
	gtk_target_list_add_text_targets(list, 0);


	_source = source;
	setDropInfo(Text, format);
	_active = true;
	_local = true;

	ct = gtk_drag_begin(source->border, list, GDK_ACTION_COPY, 1, NULL);

	if (_icon)
	{
		GdkPixbuf *icon = _icon->getIconPixbuf();
		gtk_drag_set_icon_pixbuf(ct, icon, _icon_x, _icon_y);
		if (icon != _icon->getPixbuf())
			g_object_unref(G_OBJECT(icon));
	}

	gtk_target_list_unref(list);


}
