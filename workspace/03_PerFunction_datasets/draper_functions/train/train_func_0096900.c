sdb_engine_timeout_trigger_signals (gpointer user_data)
{
	SymbolDBEngine *dbe = (SymbolDBEngine *) user_data;
	SymbolDBEnginePriv *priv;

	g_return_val_if_fail (user_data != NULL, FALSE);
	priv = dbe->priv;

	if (priv->signals_aqueue != NULL &&
	    g_async_queue_length (priv->signals_aqueue) > 0)
	{
		DBESignal *dbesig;
		gsize real_signal;
		gint process_id;

		while (priv->signals_aqueue != NULL &&
		    (dbesig = g_async_queue_try_pop (priv->signals_aqueue)) != NULL)
		{
			if (dbesig == NULL)
			{
				return g_async_queue_length (priv->signals_aqueue) > 0 ? TRUE : FALSE;
			}

			real_signal = GPOINTER_TO_INT (dbesig->value) -1;
			process_id = dbesig->process_id;

			switch (real_signal)
			{
				case SINGLE_FILE_SCAN_END:
				{
					g_signal_emit (dbe, signals[SINGLE_FILE_SCAN_END], 0);
				}
					break;

				case SCAN_BEGIN:
				{
					DEBUG_PRINT ("%s", "EMITTING scan begin.");
					g_signal_emit (dbe, signals[SCAN_BEGIN], 0, process_id);
				}
					break;

				case SCAN_END:
				{

					priv->symbols_scanned_count = 0;

					DEBUG_PRINT ("Committing symboltrans transaction...");
					gda_connection_commit_transaction (priv->db_connection, "symboltrans",
		    						NULL);
					DEBUG_PRINT ("... Done!");


					if (priv->is_first_population == TRUE)
					{

						priv->is_first_population = FALSE;
					}

					priv->is_scanning = FALSE;

					DEBUG_PRINT ("%s", "EMITTING scan-end");
					g_signal_emit (dbe, signals[SCAN_END], 0, process_id);
				}
					break;

				case SYMBOL_INSERTED:
				{
					DBESignal *dbesig2;

					dbesig2 = g_async_queue_try_pop (priv->signals_aqueue);
					g_signal_emit (dbe, signals[SYMBOL_INSERTED], 0, dbesig2->value);

					g_slice_free (DBESignal, dbesig2);
				}
					break;

				case SYMBOL_UPDATED:
				{
					DBESignal *dbesig2;

					dbesig2 = g_async_queue_try_pop (priv->signals_aqueue);
					g_signal_emit (dbe, signals[SYMBOL_UPDATED], 0, dbesig2->value);

					g_slice_free (DBESignal, dbesig2);
				}
					break;

				case SYMBOL_SCOPE_UPDATED:
				{
					DBESignal *dbesig2;

					dbesig2 = g_async_queue_try_pop (priv->signals_aqueue);
					g_signal_emit (dbe, signals[SYMBOL_SCOPE_UPDATED], 0, dbesig2->value);

					g_slice_free (DBESignal, dbesig2);
				}
					break;

				case SYMBOL_REMOVED:
				{
					DBESignal *dbesig2;

					dbesig2 = g_async_queue_try_pop (priv->signals_aqueue);
					g_signal_emit (dbe, signals[SYMBOL_REMOVED], 0, dbesig2->value);

					g_slice_free (DBESignal, dbesig2);
				}
					break;
			}

			g_slice_free (DBESignal, dbesig);
		}

		priv->trigger_closure_retries = 0;
	}
	else {
		priv->trigger_closure_retries++;
	}

	if (priv->thread_pool != NULL &&
	    g_thread_pool_unprocessed (priv->thread_pool) == 0 &&
		g_thread_pool_get_num_threads (priv->thread_pool) == 0)
	{

		g_source_remove (priv->timeout_trigger_handler);
		priv->timeout_trigger_handler = 0;
		return FALSE;
	}

	return TRUE;
}
