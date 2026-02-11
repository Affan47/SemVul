get_search_context (GeditReplaceDialog *dialog,
		    GeditDocument      *doc)
{
	GtkSourceSearchContext *search_context;

	if (doc == NULL)
	{
		return NULL;
	}

	search_context = _gedit_document_get_search_context (doc);

	if (search_context != NULL &&
	    g_object_get_data (G_OBJECT (search_context), GEDIT_SEARCH_CONTEXT_KEY) == dialog)
	{
		return search_context;
	}

	return NULL;
}
