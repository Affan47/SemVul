e_name_selector_model_peek_section (ENameSelectorModel *name_selector_model,
                                    const gchar *name,
                                    gchar **pretty_name,
                                    EDestinationStore **destination_store)
{
	Section *section;
	gint     n;

	g_return_val_if_fail (E_IS_NAME_SELECTOR_MODEL (name_selector_model), FALSE);
	g_return_val_if_fail (name != NULL, FALSE);

	n = find_section_by_name (name_selector_model, name);
	if (n < 0) {
		g_warning ("ENameSelectorModel does not have a section called '%s'!", name);
		return FALSE;
	}

	section = &g_array_index (name_selector_model->priv->sections, Section, n);

	if (pretty_name)
		*pretty_name = g_strdup (section->pretty_name);
	if (destination_store)
		*destination_store = section->destination_store;

	return TRUE;
}
