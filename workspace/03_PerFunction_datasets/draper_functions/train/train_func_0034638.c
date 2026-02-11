on_document_loaded (GeditDocument *doc,
		    const GError  *error,
		    GeditView     *view)
{
	if (error == NULL)
	{
		load_bookmark_metadata (view);
	}
}
