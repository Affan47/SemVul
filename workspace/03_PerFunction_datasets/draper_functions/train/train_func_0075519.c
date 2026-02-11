gda_connection_async_cancel (GdaConnection *cnc, guint task_id, GError **error)
{
	g_return_val_if_fail (GDA_IS_CONNECTION (cnc), FALSE);
	g_return_val_if_fail (cnc->priv->provider_obj, FALSE);

	if (! gda_connection_trylock ((GdaLockable*) cnc)) {
		g_set_error (error, GDA_CONNECTION_ERROR, GDA_CONNECTION_CANT_LOCK_ERROR,
			     _("Can't obtain connection lock"));
		return FALSE;
	}

	gint i;
	gboolean is_completed;
	gboolean retval = TRUE;
	i = get_task_index (cnc, task_id, &is_completed, FALSE);
	if ((i >= 0) && (!is_completed)) {
		CncTask *task;
		task = CNC_TASK (g_array_index (cnc->priv->waiting_tasks, gpointer, i));
		if (task->being_processed) {
			if (PROV_CLASS (cnc->priv->provider_obj)->cancel) {
				retval = PROV_CLASS (cnc->priv->provider_obj)->cancel (cnc->priv->provider_obj, cnc,
										       task->prov_task_id, error);
				if (retval) {

					g_array_remove_index (cnc->priv->waiting_tasks, i);
					cnc_task_free (task);
				}
			}
			else {
				g_set_error (error, GDA_SERVER_PROVIDER_ERROR, GDA_SERVER_PROVIDER_METHOD_NON_IMPLEMENTED_ERROR,
					     "%s", _("Provider does not support asynchronous server operation"));
				retval = FALSE;
			}
			task->being_processed = FALSE;
			if (cnc->priv->exec_times)
				g_timer_stop (task->exec_timer);
		}
		else {

			g_array_remove_index (cnc->priv->waiting_tasks, i);
			cnc_task_free (task);
		}
	}
	else if (i < 0) {
		g_set_error (error, GDA_CONNECTION_ERROR, GDA_CONNECTION_TASK_NOT_FOUND_ERROR,
			     _("Can't find task %u"), task_id);
		retval = FALSE;
	}

	gda_connection_unlock ((GdaLockable*) cnc);
	return retval;
}
