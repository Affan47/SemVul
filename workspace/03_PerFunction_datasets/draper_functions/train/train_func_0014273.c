gtk_source_completion_move_page (GtkSourceCompletion *completion,
                                 GtkScrollStep        step,
                                 gint                 num)
{
	GList *visible_providers = NULL;

	if (step == GTK_SCROLL_ENDS)
	{
		if (num > 0)
		{
			visible_providers = get_last_provider (completion);
		}
		else
		{
			visible_providers = NULL;
		}
	}
	else
	{
		if (step == GTK_SCROLL_PAGES)
		{
			num *= completion->priv->provider_page_size;
		}

		if (num > 0)
		{
			visible_providers = get_next_provider (completion, num);
		}
		else
		{
			visible_providers = get_previous_provider (completion, -1 * num);
		}
	}

	gtk_tree_view_set_model (completion->priv->tree_view_proposals, NULL);
	gtk_tree_view_columns_autosize (completion->priv->tree_view_proposals);

	gtk_source_completion_model_set_visible_providers (completion->priv->model_proposals,
							   visible_providers);

	gtk_tree_view_set_model (completion->priv->tree_view_proposals,
				 GTK_TREE_MODEL (completion->priv->model_proposals));

	update_selection_label (completion);
	check_first_selected (completion);

	g_list_free (visible_providers);
}
