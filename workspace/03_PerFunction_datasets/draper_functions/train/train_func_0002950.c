configEndElementHandler( GMarkupParseContext *psContext, const gchar *pnElementName, gpointer pUserData, GError **ppnError ) {
	struct sProfile *psProfile = pUserData;

	if ( psProfile -> psPrefsStack && !strcmp( pnElementName, "pref" ) ) {
		g_free( psProfile -> psPrefsStack -> data );
		psProfile -> psPrefsStack = g_list_delete_link( psProfile -> psPrefsStack, psProfile -> psPrefsStack );
	}
}
