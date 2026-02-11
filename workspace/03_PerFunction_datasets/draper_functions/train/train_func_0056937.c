e_source_config_get_page (ESourceConfig *config,
                          ESource *scratch_source)
{
	Candidate *candidate;
	GtkWidget *page = NULL;
	GPtrArray *array;
	gint index;

	g_return_val_if_fail (E_IS_SOURCE_CONFIG (config), NULL);
	g_return_val_if_fail (E_IS_SOURCE (scratch_source), NULL);

	array = config->priv->candidates;

	for (index = 0; page == NULL && index < array->len; index++) {
		candidate = g_ptr_array_index (array, index);
		if (e_source_equal (scratch_source, candidate->scratch_source))
			page = candidate->page;
	}

	g_return_val_if_fail (GTK_IS_BOX (page), NULL);

	return page;
}
