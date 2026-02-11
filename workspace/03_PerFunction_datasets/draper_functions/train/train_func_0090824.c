find_section_by_name (ENameSelectorDialog *name_selector_dialog,
                      const gchar *name)
{
	gint i;

	for (i = 0; i < name_selector_dialog->priv->sections->len; i++) {
		Section *section = &g_array_index (
			name_selector_dialog->priv->sections, Section, i);

		if (!strcmp (name, section->name))
			return i;
	}

	return -1;
}
