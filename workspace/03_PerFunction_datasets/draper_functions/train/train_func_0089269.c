report_idle(void *data)
{
	LList *node;

	if (!is_idle)
		return FALSE;

	for (node = accounts; node; node = node->next) {
		if (((eb_local_account *)node->data)->connected
			&& RUN_SERVICE(((eb_local_account *)node->data))->
			set_idle) {
			RUN_SERVICE(((eb_local_account *)node->data))->
				set_idle((eb_local_account *)node->data,
				idle_time);
		}
	}
	return TRUE;
}
