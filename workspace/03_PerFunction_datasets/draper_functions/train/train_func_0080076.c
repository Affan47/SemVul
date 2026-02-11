iassist_remove(IAnjutaEditorAssist* iassist,
               IAnjutaProvider* provider,
               GError** e)
{
	Sourceview* sv = ANJUTA_SOURCEVIEW(iassist);
	GtkSourceCompletion* completion = gtk_source_view_get_completion(GTK_SOURCE_VIEW(sv->priv->view));
	GList* node;
	for (node = gtk_source_completion_get_providers(completion); node != NULL; node = g_list_next(node))
	{
		SourceviewProvider* prov;
		if (!SOURCEVIEW_IS_PROVIDER(node->data))
		    continue;
		prov = SOURCEVIEW_PROVIDER(node->data);
		if (prov->iprov == provider)
		{
			DEBUG_PRINT("Removing provider: %s", ianjuta_provider_get_name(provider, NULL));
			gtk_source_completion_remove_provider(completion,
	        		                              GTK_SOURCE_COMPLETION_PROVIDER(prov),
	        		                              NULL);
	    }
	}
}
