async_subtask_compare (gconstpointer a,
                       gconstpointer b)
{
	const AsyncSubtask *subtask_a = a;
	const AsyncSubtask *subtask_b = b;


	if (subtask_a->error != NULL && subtask_b->error != NULL)
		return 0;

	if (subtask_a->error == NULL && subtask_b->error != NULL)
		return -1;

	if (subtask_a->error != NULL && subtask_b->error == NULL)
		return 1;

	if (subtask_a->priority == subtask_b->priority)
		return 0;

	return (subtask_a->priority < subtask_b->priority) ? -1 : 1;
}
