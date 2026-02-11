next_generic (Request *req, const char *detail)
{
	GError *error = NULL;
	gboolean success = FALSE;

	if (req->pending == NULL) {

		error = g_error_new_literal (NM_AGENT_MANAGER_ERROR,
		                             NM_AGENT_MANAGER_ERROR_NO_SECRETS,
		                             "No agents were available for this request.");
		req_complete_error (req, error);
		g_error_free (error);
	} else {

		req->current_has_modify = FALSE;
		req->current = req->pending->data;
		req->pending = g_slist_remove (req->pending, req->current);

		nm_log_dbg (LOGD_AGENTS, "(%s) agent %s secrets for request %p/%s",
					nm_secret_agent_get_description (req->current),
					detail, req, req->setting_name);
		success = TRUE;
	}

	return success;
}
