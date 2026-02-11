glade_gtk_radio_menu_item_set_property (GladeWidgetAdaptor *adaptor,
					GObject            *object,
					const gchar        *id,
					const GValue       *value)
{

	if (!strcmp (id, "group"))
		glade_gtk_radio_menu_item_set_group (object, value);
	else
		GWA_GET_CLASS (GTK_TYPE_MENU_ITEM)->set_property (adaptor, object,
								  id, value);
}
