glade_widget_adaptor_get_property_class (GladeWidgetAdaptor *adaptor,
					 const gchar        *name)
{
	GList *list;
	GladePropertyClass *pclass;

	for (list = adaptor->properties; list && list->data; list = list->next)
	{
		pclass = list->data;
		if (strcmp (pclass->id, name) == 0)
			return pclass;
	}
	return NULL;
}
