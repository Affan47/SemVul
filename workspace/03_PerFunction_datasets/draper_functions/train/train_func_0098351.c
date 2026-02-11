glade_widget_set_name (GladeWidget *widget, const gchar *name)
{
	g_return_if_fail (GLADE_IS_WIDGET (widget));
	if (widget->name != name)
	{
		if (widget->name)
			g_free (widget->name);

		widget->name = g_strdup (name);
		g_object_notify (G_OBJECT (widget), "name");
	}
}
