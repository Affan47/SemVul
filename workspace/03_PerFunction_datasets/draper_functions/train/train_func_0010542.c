on_complete (GkrOperation *op)
{
	GkrCallback *cb;

	g_assert (op);

	cb = g_queue_pop_tail (&op->callbacks);
	g_assert (cb);

	gkr_debug ("%p", op);


	operation_clear_callbacks (op);

	gkr_callback_invoke_bare (cb, gkr_operation_get_result (op));
	gkr_callback_free (cb);
}
