sourceview_provider_get_start_iter (GtkSourceCompletionProvider* provider,
                                    GtkSourceCompletionContext* context,
                                    GtkSourceCompletionProposal* proposal, GtkTextIter* iter)
{
	SourceviewProvider* prov = SOURCEVIEW_PROVIDER(provider);
	IAnjutaIterable* iiter = ianjuta_provider_get_start_iter (prov->iprov, NULL);
	if (iiter)
	{
		SourceviewCell* cell = SOURCEVIEW_CELL(iiter);
		GtkTextIter source_iter;
		sourceview_cell_get_iter(cell, &source_iter);
		*iter = source_iter;
		return TRUE;
	}
	else
		return FALSE;
}
