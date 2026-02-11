_e2_keybinding_sync_one (GtkTreeModel *model, GtkTreeIter *iter, GList **keys)
{
	gchar *cat, *key, *action, *action_data;
	gboolean cont;
	gtk_tree_model_get (model, iter, 0, &cat, 1, &key, 2, &cont, 3 , &action,
		4, &action_data, -1);
	gboolean valid = (*cat == '\0'
					&& *key != '\0');
	if (valid)
	{
		E2_Action *act = e2_action_check (action);
		valid = (act == NULL || !(act->exclude & E2_ACTION_EXCLUDE_ACCEL));
	}
	if (!valid)
	{
		g_free (cat);
		g_free (key);
		g_free (action);
		g_free (action_data);
		return;
	}
	GdkModifierType mask;
	guint keyval;

	gtk_accelerator_parse (key, &keyval, &mask);
	if (keyval != 0)
	{


		if (mask == 0 && (keyval < 0xF000 || keyval > 0xFFFF))
		{
			gchar *realkey = gdk_keyval_name (keyval);
			if (!g_str_equal (key, realkey))
				keyval = gdk_keyval_to_upper (keyval);
		}
		E2_KeyRuntime *k = ALLOCATE (E2_KeyRuntime);
		CHECKALLOCATEDWARN (k, )
		if (k == NULL)
		{
			g_free (cat);
			g_free (key);
			return;
		}
		k->keyval = keyval;
		k->mask = mask;
		k->action = action;
		k->action_data = action_data;
		k->cont = cont;
		k->chained = NULL;
		GtkTreeIter child_iter;
		if (gtk_tree_model_iter_children (model, &child_iter, iter))
		{
			do
			{
				_e2_keybinding_sync_one (model, &child_iter, &k->chained);
			} while (gtk_tree_model_iter_next (model, &child_iter));
		}
		*keys = g_list_append (*keys, k);
	}
	else
	{
		g_free (action);
		g_free (action_data);
	}
	g_free (cat);
	g_free (key);
	return;
}
