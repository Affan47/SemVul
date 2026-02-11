glade_widget_adaptor_get_packing_default (GladeWidgetAdaptor *child_adaptor,
					  GladeWidgetAdaptor *container_adaptor,
					  const gchar        *id)
{
	GladeChildPacking *packing = NULL;
	GList             *l;

	g_return_val_if_fail (GLADE_IS_WIDGET_ADAPTOR (child_adaptor), NULL);
	g_return_val_if_fail (GLADE_IS_WIDGET_ADAPTOR (container_adaptor), NULL);

	if ((packing =
	     glade_widget_adaptor_get_child_packing (child_adaptor,
						     container_adaptor->name)) != NULL)
	{
		for (l = packing->packing_defaults; l; l = l->next)
		{
			GladePackingDefault *def = l->data;

			if (strcmp (def->id, id) == 0)
				return def->value;
		}
	}
	return NULL;
}
