e_source_registry_dup_unique_display_name (ESourceRegistry *registry,
                                           ESource *source,
                                           const gchar *extension_name)
{
	GString *buffer;
	GList *list, *link;
	gchar *display_name;
	gboolean need_clarification = FALSE;

	g_return_val_if_fail (E_IS_SOURCE_REGISTRY (registry), NULL);
	g_return_val_if_fail (E_IS_SOURCE (source), NULL);

	list = e_source_registry_list_sources (registry, extension_name);


	link = g_list_find (list, source);
	if (link != NULL) {
		g_object_unref (link->data);
		list = g_list_remove_link (list, link);
	}


	link = g_list_find_custom (
		list, source, (GCompareFunc)
		e_source_compare_by_display_name);

	need_clarification = (link != NULL);

	g_list_free_full (list, (GDestroyNotify) g_object_unref);
	list = NULL;

	display_name = e_source_dup_display_name (source);
	buffer = g_string_new (display_name);
	g_free (display_name);

	if (need_clarification) {


		g_object_ref (source);

		while (source != NULL) {
			gchar *parent_uid;

			parent_uid = e_source_dup_parent (source);

			g_object_unref (source);
			source = NULL;

			if (parent_uid != NULL) {
				source = e_source_registry_ref_source (
					registry, parent_uid);
				g_free (parent_uid);
			}

			if (source != NULL) {
				g_object_ref (source);
				list = g_list_prepend (list, source);
			}
		}


		if (list != NULL)
			g_string_append (buffer, " (");

		for (link = list; link != NULL; link = g_list_next (link)) {
			if (link != list)
				g_string_append (buffer, " / ");

			source = E_SOURCE (link->data);
			display_name = e_source_dup_display_name (source);
			g_string_append (buffer, display_name);
			g_free (display_name);
		}

		if (list != NULL)
			g_string_append (buffer, ")");

		g_list_free_full (list, (GDestroyNotify) g_object_unref);
	}

	return g_string_free (buffer, FALSE);
}
