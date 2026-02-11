nemo_icon_container_select_list_unselect_others (NemoIconContainer *container,
						     GList *selection)
{
	gboolean selection_changed;
	GHashTable *hash;
	GList *p;
	NemoIcon *icon;

	g_return_if_fail (NEMO_IS_ICON_CONTAINER (container));

	selection_changed = FALSE;

	hash = g_hash_table_new (NULL, NULL);
	for (p = selection; p != NULL; p = p->next) {
		g_hash_table_insert (hash, p->data, p->data);
	}
	for (p = container->details->icons; p != NULL; p = p->next) {
		icon = p->data;

		selection_changed |= icon_set_selected
			(container, icon,
			 g_hash_table_lookup (hash, icon) != NULL);
	}
	g_hash_table_destroy (hash);

	if (selection_changed) {
		g_signal_emit (container,
				 signals[SELECTION_CHANGED], 0);
	}
}
