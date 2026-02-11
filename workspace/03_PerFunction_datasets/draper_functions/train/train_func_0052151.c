update_icon(GObject *obj G_GNUC_UNUSED, GParamSpec *param, SexyIconEntry *entry)
{
	if (param != NULL)
	{
		const char *name = g_param_spec_get_name(param);

		if (strcmp(name, "pixbuf")   && strcmp(name, "stock")  &&
			strcmp(name, "image")    && strcmp(name, "pixmap") &&
			strcmp(name, "icon_set") && strcmp(name, "pixbuf_animation"))
		{
			return;
		}
	}

	gtk_widget_queue_resize(GTK_WIDGET(entry));
}
