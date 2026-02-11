gtt_task_get_secs_earliest (GttTask *tsk)
{
	GList *node;
	if (NULL == tsk->interval_list) return 0;

	time_t earliest = INT_MAX;

	for (node=tsk->interval_list; node; node=node->next)
	{
		GttInterval * ivl = node->data;
		if (ivl->start < earliest) earliest = ivl->start;
	}
	return earliest;
}
