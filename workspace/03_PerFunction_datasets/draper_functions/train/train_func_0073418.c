glade_widget_change_signal_handler_impl (GladeWidget *widget,
					 GladeSignal *old_signal_handler,
					 GladeSignal *new_signal_handler)
{
	GPtrArray   *signals;
	GladeSignal *signal_handler_iter;
	guint        i;

	g_return_if_fail (GLADE_IS_WIDGET (widget));
	g_return_if_fail (GLADE_IS_SIGNAL (old_signal_handler));
	g_return_if_fail (GLADE_IS_SIGNAL (new_signal_handler));
	g_return_if_fail (strcmp (old_signal_handler->name, new_signal_handler->name) == 0);

	signals = glade_widget_list_signal_handlers (widget, old_signal_handler->name);


	g_assert (signals);

	for (i = 0; i < signals->len; i++)
	{
		signal_handler_iter = g_ptr_array_index (signals, i);
		if (glade_signal_equal (signal_handler_iter, old_signal_handler))
		{
			if (strcmp (old_signal_handler->handler,
				    new_signal_handler->handler) != 0)
			{
				g_free (signal_handler_iter->handler);
				signal_handler_iter->handler =
					g_strdup (new_signal_handler->handler);
			}


			if (signal_handler_iter->handler)
				g_free (signal_handler_iter->handler);
			signal_handler_iter->handler =
				g_strdup (new_signal_handler->handler);


			if (signal_handler_iter->userdata)
				g_free (signal_handler_iter->userdata);
			signal_handler_iter->userdata =
				g_strdup (new_signal_handler->userdata);

			signal_handler_iter->after    = new_signal_handler->after;
			signal_handler_iter->swapped  = new_signal_handler->swapped;
			break;
		}
	}
}
