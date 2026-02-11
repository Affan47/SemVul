populate_store (GladeEPropIconSources *eprop_sources)
{
	GladeIconSources *sources = NULL;

	gtk_tree_store_clear (eprop_sources->store);
	gtk_list_store_clear (eprop_sources->icon_names_store);

	if (!GLADE_EDITOR_PROPERTY (eprop_sources)->property)
		return;

	glade_property_get (GLADE_EDITOR_PROPERTY (eprop_sources)->property, &sources);

	if (sources)
		g_hash_table_foreach (sources->sources, (GHFunc)populate_store_foreach, eprop_sources);

}
