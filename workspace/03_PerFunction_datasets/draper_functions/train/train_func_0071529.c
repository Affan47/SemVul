glade_signal_model_iter_next (GtkTreeModel *model, GtkTreeIter *iter)
{
  const gchar *widget;
  GladeSignal *handler;
  GtkTreeIter parent;
  GladeSignalModel *sig_model;

  g_return_val_if_fail (iter != NULL, FALSE);
  g_return_val_if_fail (GLADE_IS_SIGNAL_MODEL(model), FALSE);

  widget = iter->user_data;
  handler = iter->user_data2;

  sig_model = GLADE_SIGNAL_MODEL (model);

  gtk_tree_model_iter_parent (model, &parent, iter);

  if (handler)
    {
      const GladeSignalClass *sig_class = glade_signal_get_class (handler);
      GList *signals =
	glade_signal_model_create_signal_list (sig_model,
					       widget);
      GList* signal = g_list_find (signals, sig_class);
      GPtrArray* handlers = g_hash_table_lookup (sig_model->priv->signals,
						 glade_signal_class_get_name (sig_class));
      if (glade_signal_model_is_dummy_handler (sig_model, handler))
	{
	  return glade_signal_model_iter_next_signal (sig_model, widget, iter, signal);
	}
      else if (handlers)
	{
	  gint new_index = g_ptr_array_find (handlers, handler) + 1;
	  if (new_index < handlers->len)
	    {
	      glade_signal_model_create_signal_iter (sig_model, widget,
						     g_ptr_array_index (handlers, new_index),
						     iter);
	      g_list_free (signals);
	      return TRUE;
	    }
	  else if (new_index == handlers->len)
	    {
	      glade_signal_model_create_signal_iter (sig_model, widget,
						     glade_signal_model_get_dummy_handler (sig_model,
											   sig_class),
						     iter);
	      g_list_free (signals);
	      return TRUE;
	    }
	  else
	    {
	      return glade_signal_model_iter_next_signal (sig_model, widget, iter, signal);
	    }
	}
      else
	{
	  g_list_free (signals);
	  return FALSE;
	}
    }
  else if (widget)
    {
      gint new_index = g_list_index (sig_model->priv->widgets, widget) + 1;

      return gtk_tree_model_iter_nth_child (model, iter, NULL, new_index);
    }
  iter->user_data = NULL;
  iter->user_data2 = NULL;
  iter->user_data3 = NULL;
  iter->stamp = 0;
  return FALSE;
}
