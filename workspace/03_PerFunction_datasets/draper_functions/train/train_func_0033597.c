active_prompt_unref (gpointer data)
{
	ActivePrompt *active = data;

	if (g_atomic_int_dec_and_test (&active->refs)) {
		callback_free (active->callback);
		g_object_unref (active->prompter);
		g_object_unref (active->cancellable);
		if (g_signal_handler_is_connected (active->prompt, active->notify_sig))
			g_signal_handler_disconnect (active->prompt, active->notify_sig);
		if (g_signal_handler_is_connected (active->prompt, active->close_sig))
			g_signal_handler_disconnect (active->prompt, active->close_sig);
		g_object_unref (active->prompt);
		g_hash_table_destroy (active->changed);
		if (active->exchange)
			g_object_unref (active->exchange);
		g_slice_free (ActivePrompt, active);
	}
}
