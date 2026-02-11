on_thread_group_removed(GArray *nodes)
{
	ThreadGroup *group = find_thread_group(parse_lead_value(nodes));

	if (group)
	{
		thread_group_free(group);
		array_remove(thread_groups, group);
	}
}
