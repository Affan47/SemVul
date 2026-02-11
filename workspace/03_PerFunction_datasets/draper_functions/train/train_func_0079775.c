compose_close(Compose *compose)
{
	gint x, y;

	if (!g_mutex_trylock(compose->mutex)) {


		debug_print("waiting for drafting to finish...\n");
		compose_allow_user_actions(compose, FALSE);
		g_timeout_add (500, (GSourceFunc) compose_close, compose);
		return FALSE;
	}
	cm_return_val_if_fail(compose, FALSE);
	gtkut_widget_get_uposition(compose->window, &x, &y);
	if (!compose->batch) {
		prefs_common.compose_x = x;
		prefs_common.compose_y = y;
	}
	g_mutex_unlock(compose->mutex);
	compose_destroy(compose);
	return FALSE;
}
