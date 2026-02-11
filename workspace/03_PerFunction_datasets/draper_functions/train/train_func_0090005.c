glade_gtk_notebook_get_child_property (GladeWidgetAdaptor *adaptor,
				       GObject            *container,
				       GObject            *child,
				       const gchar        *property_name,
				       GValue             *value)
{
	gint position;

	if (strcmp (property_name, "position") == 0)
	{
		if (g_object_get_data (child, "special-child-type") != NULL)
		{
			if ((position = notebook_search_tab (GTK_NOTEBOOK (container),
							     GTK_WIDGET (child))) >= 0)
				g_value_set_int (value, position);
			else
				g_value_set_int (value, 0);
		}
		else
			gtk_container_child_get_property (GTK_CONTAINER (container),
							  GTK_WIDGET (child),
							  property_name,
							  value);
	}

	else if (g_object_get_data (child, "special-child-type") == NULL)
		gtk_container_child_get_property (GTK_CONTAINER (container),
						  GTK_WIDGET (child),
						  property_name,
						  value);
}
