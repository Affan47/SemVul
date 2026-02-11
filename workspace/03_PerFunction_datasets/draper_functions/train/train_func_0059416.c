pm_job_free (PmJob *job)
{
	if (job->error != NULL) g_error_free (job->error);
	if (job->map != NULL) g_hash_table_destroy (job->map);
	if (job->file != NULL) g_object_unref (job->file);
	if (job->name != NULL) g_free (job->name);
	if (job->sibling != NULL) g_object_unref (job->sibling);
	if (job->parent != NULL) g_object_unref (job->parent);
	if (job->node != NULL) g_object_unref (job->node);
}
