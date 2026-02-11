glade_gtk_table_set_child_property (GladeWidgetAdaptor *adaptor,
				    GObject            *container,
				    GObject            *child,
				    const gchar        *property_name,
				    GValue             *value)
{
	g_return_if_fail (GTK_IS_TABLE (container));
	g_return_if_fail (GTK_IS_WIDGET (child));
	g_return_if_fail (property_name != NULL && value != NULL);

	GWA_GET_CLASS
		(GTK_TYPE_CONTAINER)->child_set_property (adaptor,
							  container, child,
							  property_name, value);

	if (strcmp (property_name, "bottom-attach") == 0 ||
	    strcmp (property_name, "left-attach") == 0 ||
	    strcmp (property_name, "right-attach") == 0 ||
	    strcmp (property_name, "top-attach") == 0)
	{

		glade_gtk_table_refresh_placeholders (GTK_TABLE (container));
	}

}
