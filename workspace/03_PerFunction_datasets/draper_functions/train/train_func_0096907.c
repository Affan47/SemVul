glade_gtk_cell_renderer_set_property (GladeWidgetAdaptor *adaptor,
				      GObject *object,
				      const gchar *property_name,
				      const GValue *value)
{
	static gint use_attr_len = 0;
	static gint attr_len     = 0;

	if (!attr_len)
	{
		use_attr_len = strlen ("use-attr-");
		attr_len = strlen ("attr-");
	}

	if (strncmp (property_name, "use-attr-", use_attr_len) == 0)
		glade_gtk_cell_renderer_set_use_attribute (object, &property_name[use_attr_len], value);
	else if (strncmp (property_name, "attr-", attr_len) == 0)
		glade_gtk_cell_renderer_sync_attributes (object);
	else if (glade_gtk_cell_renderer_property_enabled (object, property_name))

		GWA_GET_CLASS (G_TYPE_OBJECT)->set_property (adaptor,
							     object,
							     property_name,
							     value);
}
