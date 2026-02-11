glade_signal_model_iter_nth_child (GtkTreeModel *model,
                                   GtkTreeIter *iter,
                                   GtkTreeIter *parent,
                                   gint n)
{
  GladeSignal *handler;
  GladeSignalModel *sig_model;
  const gchar *widget;

  g_return_val_if_fail (iter != NULL, 0);
  g_return_val_if_fail (GLADE_IS_SIGNAL_MODEL(model), 0);

  handler = parent ? parent->user_data2 : NULL;
  sig_model = GLADE_SIGNAL_MODEL (model);
  widget = parent ? parent->user_data : NULL;

  if (handler)
    {
      return FALSE;
    }
  else if (widget)
    {
      GList *signals = glade_signal_model_create_signal_list (sig_model,
							      widget);
      GList *signal;
      for (signal = signals; signal != NULL; signal = g_list_next (signal))
	{
	  GPtrArray *handlers = g_hash_table_lookup (sig_model->priv->signals,
						     glade_signal_class_get_name (signal->data));
	  if (handlers)
	    {
	      if (n >= handlers->len)
		n -= handlers->len;
	      else
		{
		  glade_signal_model_create_signal_iter (sig_model,
							 widget,
							 g_ptr_array_index (handlers, n),
							 iter);
		  g_list_free (signals);
		  return TRUE;
		}
	    }
	  if (n == 0)
	    {
	      GladeSignal *handler =
		glade_signal_model_get_dummy_handler (sig_model,
						      signal->data);
	      glade_signal_model_create_signal_iter (sig_model,
						     widget,
						     handler,
						     iter);
	      g_list_free (signals);
	      return TRUE;
	    }
	  n--;
	}
      return FALSE;
    }
  else
    {
      if (g_list_length (sig_model->priv->widgets) > n)
	{
	  glade_signal_model_create_widget_iter (sig_model,
						 g_list_nth_data (sig_model->priv->widgets, n),
						 iter);
	  return TRUE;
	}
    }
  return FALSE;
}
