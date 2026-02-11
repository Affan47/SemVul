iproject_load_node (IAnjutaProject *obj, AnjutaProjectNode *node, GError **error)
{
	PmJob *load_job;

	if (node == NULL) node = ANJUTA_PROJECT_NODE (obj);
	if (AMP_PROJECT (obj)->queue == NULL) AMP_PROJECT (obj)->queue = pm_command_queue_new ();

	AMP_PROJECT (obj)->loading++;
	load_job = pm_job_new (&amp_load_job, node, NULL, NULL, ANJUTA_PROJECT_UNKNOWN, NULL, NULL, obj);

	pm_command_queue_push (AMP_PROJECT (obj)->queue, load_job);

	return TRUE;
}
