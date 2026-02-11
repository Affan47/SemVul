glade_widget_set_support_warning (GladeWidget *widget,
				  const gchar *warning)
{
	g_return_if_fail (GLADE_IS_WIDGET (widget));

	if (widget->support_warning)
		g_free (widget->support_warning);
	widget->support_warning = g_strdup (warning);

	g_object_notify (G_OBJECT (widget), "support-warning");
}
