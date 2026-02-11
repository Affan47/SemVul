on_real_close_content (GSQLContent *content, gboolean force)
{
	GSQL_TRACE_FUNC;

	GSQLPRunnerExecOptions *eopt;

	eopt = g_object_get_data (G_OBJECT (content), "eopt");

	if (!eopt)
		return;

	eopt->run_state = FALSE;

	gsql_thread_join (eopt->thread);

	g_free (eopt);

}
