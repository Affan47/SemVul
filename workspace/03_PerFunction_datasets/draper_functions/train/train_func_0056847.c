theme_load_from_uri (char const *uri)
{
	struct theme_load_state	state;
	GsfInput *input = go_file_open (uri, NULL);

	if (input == NULL) {
		g_warning ("[GogTheme]: Could not open %s", uri);
		return;
	}
	state.theme = NULL;
	state.desc = state.lang = state.name = NULL;
	state.langs = g_get_language_names ();
	state.name_lang_score = state.desc_lang_score = G_MAXINT;
	if (!xml)
		xml = gsf_xml_in_doc_new (theme_dtd, NULL);
	if (!gsf_xml_in_doc_parse (xml, input, &state))
		g_warning ("[GogTheme]: Could not parse %s", uri);
	if (state.theme != NULL) {
		if (!go_file_access (uri, GO_W_OK)) {
			state.theme->uri = g_strdup (uri);
			if (state.theme->id == NULL) {
				state.theme->id = go_uuid ();
				gog_theme_save (state.theme);
			}
			state.theme->type = GO_RESOURCE_RW;
		} else {
			if (state.theme->id == NULL) {

				char *name = g_hash_table_lookup (state.theme->names, "C");
				if (name)
					state.theme->id = g_strdup (name);
				else
					g_warning ("[GogTheme]: Theme with no Id in %s", uri);
			}
			state.theme->type = GO_RESOURCE_RO;
		}
		theme_loaded (&state);
		gog_theme_registry_add (state.theme, FALSE);
	} else {
		g_free (state.name);
		g_free (state.desc);
	}
	g_free (state.lang);
	g_object_unref (input);
}
