git_log_data_command_init (GitLogDataCommand *self)
{
	self->priv = g_new0 (GitLogDataCommandPriv, 1);
	self->priv->input_queue = g_async_queue_new_full (g_free);
	self->priv->output_queue = g_queue_new ();
	self->priv->revisions = g_hash_table_new_full (g_str_hash, g_str_equal,
												   g_free, g_object_unref);
	self->priv->commit_regex = g_regex_new (COMMIT_REGEX, 0, 0, NULL);
	self->priv->parent_regex = g_regex_new (PARENT_REGEX, 0, 0, NULL);
	self->priv->author_regex = g_regex_new (AUTHOR_REGEX, 0, 0, NULL);
	self->priv->time_regex = g_regex_new (TIME_REGEX, 0, 0, NULL);
	self->priv->short_log_regex = g_regex_new (SHORT_LOG_REGEX, 0, 0, NULL);
}
