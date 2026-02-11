pk_task_user_declined_idle_cb (PkTaskState *state)
{
	GError *error;


	if (state->simulate) {
		error = g_error_new (PK_CLIENT_ERROR, PK_CLIENT_ERROR_DECLINED_SIMULATION, "user declined simulation");
		pk_task_generic_state_finish (state, error);
		g_error_free (error);
		goto out;
	}


	g_debug ("declined request %i", state->request);
	error = g_error_new (PK_CLIENT_ERROR, PK_CLIENT_ERROR_FAILED, "user declined interaction");
	pk_task_generic_state_finish (state, error);
	g_error_free (error);

out:

	return FALSE;
}
