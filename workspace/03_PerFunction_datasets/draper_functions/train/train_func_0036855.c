glade_widget_set_internal (GladeWidget *widget, const gchar *internal)
{
	g_return_if_fail (GLADE_IS_WIDGET (widget));
	if (widget->internal != internal) {
		g_free (widget->internal);
		widget->internal = g_strdup (internal);
		g_object_notify (G_OBJECT (widget), "internal");
	}
}
