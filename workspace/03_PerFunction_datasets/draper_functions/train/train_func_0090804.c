proposal_has_info (GtkSourceCompletionProvider *provider,
		   GtkSourceCompletionProposal *proposal)
{
	gchar *info;

	if (gtk_source_completion_provider_get_info_widget (provider, proposal) != NULL)
	{
		return TRUE;
	}

	info = gtk_source_completion_proposal_get_info (proposal);

	if (info != NULL)
	{
		g_free (info);
		return TRUE;
	}

	return FALSE;
}
