glade_gtk_icon_factory_set_property (GladeWidgetAdaptor *adaptor,
				     GObject *object,
				     const gchar *property_name,
				     const GValue *value)
{
	if (strcmp (property_name, "sources") == 0)
	{
		glade_gtk_icon_factory_set_sources (object, value);
	}
	else

		GWA_GET_CLASS (G_TYPE_OBJECT)->set_property (adaptor,
							     object,
							     property_name,
							     value);
}
