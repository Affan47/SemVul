gkr_callback_invoke_res (GkrCallback *cb,
                         GnomeKeyringResult res)
{
	g_assert (cb != NULL);
	g_assert (cb->callback != NULL);

	if (cb->operation && !gkr_operation_set_result (cb->operation, res))
		return;

	gkr_callback_invoke_bare (cb, res);
}
