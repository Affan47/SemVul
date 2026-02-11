_gth_rename_task_exec (GthRenameTask *self)
{
	GFile     *source;
	GFile     *destination;

	if (self->priv->current_old == NULL) {
		gth_task_completed (GTH_TASK (self), NULL);
		return;
	}

	source = (GFile *) self->priv->current_old->data;
	destination = (GFile *) self->priv->current_new->data;

	_gth_rename_task_try_rename (self, source, destination, 0);
}
