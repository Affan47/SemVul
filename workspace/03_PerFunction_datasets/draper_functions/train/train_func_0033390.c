search_condition_expr(GtkMenuItem *widget, gpointer data)
{
	gchar * cond_str;
	MatcherList * matchers = NULL;

	cm_return_val_if_fail(
			mainwindow_get_mainwindow()->summaryview->quicksearch != NULL,
			FALSE);


	cond_str = quicksearch_get_text(mainwindow_get_mainwindow()->summaryview->quicksearch);

	if (*cond_str != '\0') {
		matchers = matcher_parser_get_cond((gchar*)cond_str, NULL);
	}

	prefs_matcher_open(matchers, search_condition_expr_done);

	if (matchers != NULL)
		matcherlist_free(matchers);

	g_free(cond_str);

	return TRUE;
}
