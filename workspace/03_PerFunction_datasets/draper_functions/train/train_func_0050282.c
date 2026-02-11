quicksearch_add_to_history(QuickSearch* quicksearch)
{
	gchar* search_string = quicksearch->request.matchstring;


	if (quicksearch->want_history && !quicksearch->in_typing && search_string && strlen(search_string) != 0) {
		switch (prefs_common.summary_quicksearch_type) {
			case ADVANCED_SEARCH_EXTENDED:
				if (advsearch_has_proper_predicate(quicksearch->asearch)) {
					quicksearch->extended_search_strings =
						add_history(quicksearch->extended_search_strings,
								g_strdup(search_string));
					prefs_common.summary_quicksearch_history =
						add_history(prefs_common.summary_quicksearch_history,
								g_strdup(search_string));
				}
				break;
			default:
				quicksearch->normal_search_strings =
					add_history(quicksearch->normal_search_strings,
							g_strdup(search_string));
				prefs_common.summary_quicksearch_history =
					add_history(prefs_common.summary_quicksearch_history,
							g_strdup(search_string));
				break;
		}

		quicksearch_set_popdown_strings(quicksearch);
	}

	quicksearch->want_history = FALSE;
}
