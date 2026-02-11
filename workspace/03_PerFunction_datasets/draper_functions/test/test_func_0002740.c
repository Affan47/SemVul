glade_widget_change_signal_handler (GladeWidget * widget,
                                    const GladeSignal * old_signal_handler,
                                    const GladeSignal * new_signal_handler)
{
  GPtrArray *signals;
  GladeSignal *signal_handler_iter;
  guint i;

  g_return_if_fail (GLADE_IS_WIDGET (widget));
  g_return_if_fail (GLADE_IS_SIGNAL (old_signal_handler));
  g_return_if_fail (GLADE_IS_SIGNAL (new_signal_handler));
  g_return_if_fail (strcmp (glade_signal_get_name (old_signal_handler),
			    glade_signal_get_name (new_signal_handler)) == 0);

  signals =
    glade_widget_list_signal_handlers (widget, glade_signal_get_name (old_signal_handler));


  g_assert (signals);

  for (i = 0; i < signals->len; i++)
    {
      signal_handler_iter = g_ptr_array_index (signals, i);
      if (glade_signal_equal (signal_handler_iter, old_signal_handler))
        {

	  glade_signal_set_detail (signal_handler_iter,
				   glade_signal_get_detail (new_signal_handler));


	  glade_signal_set_handler (signal_handler_iter,
				    glade_signal_get_handler (new_signal_handler));


	  glade_signal_set_userdata (signal_handler_iter,
				     glade_signal_get_userdata (new_signal_handler));


	  glade_signal_set_after (signal_handler_iter,
				  glade_signal_get_after (new_signal_handler));
	  glade_signal_set_swapped (signal_handler_iter,
				    glade_signal_get_swapped (new_signal_handler));

	  g_signal_emit (widget, glade_widget_signals[CHANGE_SIGNAL_HANDLER], 0,
	                 signal_handler_iter);

	  break;
        }
    }
}
