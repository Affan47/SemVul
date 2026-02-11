column_types_store_populate_enums_flags (GtkListStore *store,
					 gboolean      enums)
{
	GtkTreeIter iter;
	GList *types = NULL, *list, *l;
	GList *adaptors = glade_widget_adaptor_list_adaptors ();

	for (list = adaptors; list; list = list->next)
	{
		GladeWidgetAdaptor *adaptor = list->data;
		GladePropertyClass *pclass;

		for (l = adaptor->properties; l; l = l->next)
		{
			pclass = l->data;


			if (strcmp (g_type_name (pclass->pspec->value_type), "GladeGtkGnomeUIInfo") == 0 ||
			    strcmp (g_type_name (pclass->pspec->value_type), "GladeStock") == 0 ||
			    strcmp (g_type_name (pclass->pspec->value_type), "GladeStockImage") == 0 ||
			    strcmp (g_type_name (pclass->pspec->value_type), "GladeGtkImageType") == 0 ||
			    strcmp (g_type_name (pclass->pspec->value_type), "GladeGtkButtonType") == 0 ||
			    strcmp (g_type_name (pclass->pspec->value_type), "GladeGnomeDruidPagePosition") == 0 ||
			    strcmp (g_type_name (pclass->pspec->value_type), "GladeGnomeIconListSelectionMode") == 0 ||
			    strcmp (g_type_name (pclass->pspec->value_type), "GladeGnomeMessageBoxType") == 0)
				continue;

			if ((enums ? G_TYPE_IS_ENUM (pclass->pspec->value_type) :
			     G_TYPE_IS_FLAGS (pclass->pspec->value_type)) &&
			    !g_list_find_custom (types, g_type_name (pclass->pspec->value_type),
						 (GCompareFunc)find_by_type_name))
				types = g_list_prepend (types, g_strdup (g_type_name (pclass->pspec->value_type)));

		}
	}
	g_list_free (adaptors);

	types = g_list_sort (types, (GCompareFunc)find_by_type_name);

	for (l = types; l; l = l->next)
	{
		gchar *type_name = l->data;

		gtk_list_store_append (store, &iter);
		gtk_list_store_set (store, &iter,
				    COLUMN_NAME, type_name,
				    -1);
		g_free (type_name);
	}
	g_list_free (types);
}
