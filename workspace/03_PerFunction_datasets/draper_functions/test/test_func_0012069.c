pk_task_user_accepted_idle_cb (PkTaskState *state)
{

	if (state->exit_enum == PK_EXIT_ENUM_KEY_REQUIRED) {
		g_debug ("need to do install-sig");
		pk_task_install_signatures (state);
		goto out;
	}


	if (state->exit_enum == PK_EXIT_ENUM_EULA_REQUIRED) {
		g_debug ("need to do accept-eula");
		pk_task_accept_eulas (state);
		goto out;
	}


	g_debug ("continuing with request %i", state->request);
	pk_task_do_async_action (state);

out:

	return FALSE;
}
