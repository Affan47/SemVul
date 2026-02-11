_e2_command_line_sync_history (E2_CommandLineRuntime *rt)
{

	if (rt->history != NULL)
		e2_list_free_with_data (&rt->history);
	GtkTreeIter iter;


	if (gtk_tree_model_get_iter_first (rt->model, &iter))
	{
		gint count = 0;
		gint max = (rt->original) ?
			e2_option_int_get ("command-line-history-max"):
			e2_option_int_get ("dir-line-history-max");
		gchar *value;
		do
		{
			gtk_tree_model_get (rt->model, &iter, 0, &value, -1);
			rt->history = g_list_append (rt->history, value);
			if (++count == max)
				break;
		} while (gtk_tree_model_iter_next (rt->model, &iter));
	}
}
