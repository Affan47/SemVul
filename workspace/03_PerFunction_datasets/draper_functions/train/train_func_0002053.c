iassist_proposals(IAnjutaEditorAssist* iassist,
                  IAnjutaProvider* provider,
                  GList* proposals,
                  const gchar* pre_word,
                  gboolean finished,
                  GError** e)
{
	Sourceview* sv = ANJUTA_SOURCEVIEW(iassist);
	GtkSourceCompletion* completion = gtk_source_view_get_completion(GTK_SOURCE_VIEW(sv->priv->view));
	GList* node;
	for (node = gtk_source_completion_get_providers(completion); node != NULL; node = g_list_next(node))
	{
		SourceviewProvider* prov;
		if (!SOURCEVIEW_IS_PROVIDER (node->data))
			continue;

		prov = SOURCEVIEW_PROVIDER(node->data);
		if (prov->iprov == provider)
		{
			g_return_if_fail (!prov->cancelled);

			GList* prop;
			GList* items = NULL;
			for (prop = proposals; prop != NULL; prop = g_list_next(prop))
			{
				IAnjutaEditorAssistProposal* proposal = prop->data;
				GtkSourceCompletionItem* item;
				if (proposal->markup)
				{
					item = gtk_source_completion_item_new_with_markup(proposal->markup,
					                                                  proposal->text,
					                                                  proposal->icon,
					                                                  proposal->info);
				}
				else
				{
					item = gtk_source_completion_item_new(proposal->label,
					                                      proposal->text,
					                                      proposal->icon,
					                                      proposal->info);
				}
				items = g_list_append (items, item);
				g_object_set_data (G_OBJECT(item), "__data", proposal->data);
			}
			gtk_source_completion_context_add_proposals (prov->context, GTK_SOURCE_COMPLETION_PROVIDER(prov),
			                                             items, finished);
			g_list_free_full (items, g_object_unref);
			break;
		}
	}
}
