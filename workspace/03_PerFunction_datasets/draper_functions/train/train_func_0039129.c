update_variables_values (SnippetsInteraction *snippets_interaction,
	                     IAnjutaIterable *iter,
	                     gint modified_value,
                         gchar *text)
{
	SnippetsInteractionPrivate *priv = NULL;
	GList *iter1 = NULL, *iter2 = NULL, *edited_app_node = NULL;
	SnippetVariableInfo *var_info = NULL;
	IAnjutaIterable *var_iter = NULL, *start_iter = NULL, *end_iter = NULL;
	gboolean found = FALSE;
	gint diff = 0;


	g_return_if_fail (ANJUTA_IS_SNIPPETS_INTERACTION (snippets_interaction));
	priv = ANJUTA_SNIPPETS_INTERACTION_GET_PRIVATE (snippets_interaction);
	g_return_if_fail (priv->editing);
	g_return_if_fail (priv->editing_info);
	if (priv->changing_values_blocker)
		return;
	priv->changing_values_blocker = TRUE;


	for (iter1 = priv->editing_info->snippet_vars_info; iter1 != NULL; iter1 = g_list_next (iter1))
	{
		found = FALSE;
		var_info = (SnippetVariableInfo *)iter1->data;

		for (iter2 = g_list_first (var_info->appearances); iter2 != NULL; iter2 = g_list_next (iter2))
		{
			var_iter = IANJUTA_ITERABLE (iter2->data);
			g_return_if_fail (IANJUTA_IS_ITERABLE (var_iter));


			diff = ianjuta_iterable_diff (var_iter, iter, NULL);

			if ((diff == 0) ||
			    (diff > 0 && diff <= var_info->cur_value_length))
			{
				edited_app_node = iter2;
				found = TRUE;
				var_info->cur_value_length += modified_value;

				break;
			}
		}
		if (found) break;

	}

	if (found)
	{
		g_return_if_fail (edited_app_node != NULL);


		for (iter1 = g_list_first (edited_app_node); iter1 != NULL; iter1 = g_list_next (iter1))
		{

			if (iter1 == edited_app_node)
				continue;

			var_iter = IANJUTA_ITERABLE (iter1->data);
			g_return_if_fail (IANJUTA_IS_ITERABLE (var_iter));

			start_iter = ianjuta_iterable_clone (var_iter, NULL);
			ianjuta_iterable_set_position (start_iter,
			                               ianjuta_iterable_get_position (var_iter, NULL) + diff,
			                               NULL);
			end_iter = ianjuta_iterable_clone (var_iter, NULL);
			ianjuta_iterable_set_position (end_iter,
			                               ianjuta_iterable_get_position (var_iter, NULL) + diff - modified_value,
			                               NULL);

			if (modified_value > 0)
			{
				ianjuta_editor_insert (priv->cur_editor, start_iter, text, modified_value, NULL);
			}
			else
			{
				ianjuta_editor_erase (priv->cur_editor, start_iter, end_iter, NULL);
			}

			g_object_unref (start_iter);
			g_object_unref (end_iter);
		}
	}


	priv->changing_values_blocker = FALSE;
}
