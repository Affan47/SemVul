gwa_inherit_child_packing (GladeWidgetAdaptor *adaptor)
{
	GladeWidgetAdaptor *parent_adaptor;
	GList              *child_packings = NULL, *packing_list, *default_list;

	if ((parent_adaptor = gwa_get_parent_adaptor (adaptor)) != NULL)
	{
		for (packing_list = parent_adaptor->child_packings;
		     packing_list; packing_list = packing_list->next)
		{
			GladeChildPacking *packing     = packing_list->data;
			GladeChildPacking *packing_dup = g_new0 (GladeChildPacking, 1);

			packing_dup->parent_name = g_strdup (packing->parent_name);

			for (default_list = packing->packing_defaults;
			     default_list; default_list = default_list->next)
			{
				GladePackingDefault *def     = default_list->data;
				GladePackingDefault *def_dup = g_new0 (GladePackingDefault, 1);

				def_dup->id    = g_strdup (def->id);
				def_dup->value = g_strdup (def->value);

				packing_dup->packing_defaults =
					g_list_prepend (packing_dup->packing_defaults, def_dup);
			}

			child_packings = g_list_prepend (child_packings, packing_dup);
		}
	}
	return child_packings;
}
