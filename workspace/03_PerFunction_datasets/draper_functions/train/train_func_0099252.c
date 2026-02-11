glade_widget_pack_property_default (GladeWidget *widget,
				    const gchar *id_property)
{
	GladeProperty *property;

	g_return_val_if_fail (GLADE_IS_WIDGET (widget), FALSE);

	if ((property = glade_widget_get_pack_property (widget, id_property)) != NULL)
		return glade_property_default (property);

	return FALSE;
}
