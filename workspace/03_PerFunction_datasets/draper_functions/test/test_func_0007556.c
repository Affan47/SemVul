pk_task_find_by_request (PkTask *task, guint request)
{
	PkTaskState *item;
	guint i;
	GPtrArray *array;

	g_return_val_if_fail (PK_IS_TASK (task), NULL);
	g_return_val_if_fail (request != 0, NULL);

	array = task->priv->array;
	for (i = 0; i < array->len; i++) {
		item = g_ptr_array_index (array, i);
		if (item->request == request)
			goto out;
	}
	item = NULL;
out:
	return item;
}
