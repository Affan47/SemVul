nm_ppp_manager_start (NMPPPManager *manager,
                      NMActRequest *req,
                      const char *ppp_name,
                      guint32 timeout_secs,
                      GError **err)
{
	NMPPPManagerPrivate *priv;
	NMConnection *connection;
	NMSettingPPP *s_ppp;
	gboolean s_ppp_created = FALSE;
	NMSettingPPPOE *pppoe_setting;
	NMSettingAdsl *adsl_setting;
	NMCmdLine *ppp_cmd;
	char *cmd_str;
	struct stat st;
	int ignored;

	g_return_val_if_fail (NM_IS_PPP_MANAGER (manager), FALSE);
	g_return_val_if_fail (NM_IS_ACT_REQUEST (req), FALSE);

	priv = NM_PPP_MANAGER_GET_PRIVATE (manager);

#if !WITH_PPP

	g_set_error_literal (err,
	                     NM_PPP_MANAGER_ERROR,
	                     NM_PPP_MANAGER_ERROR_UNKOWN,
	                     "PPP support is not enabled.");
	return FALSE;
#endif

	priv->pid = 0;


	if (stat ("/dev/ppp", &st) || !S_ISCHR (st.st_mode))
		ignored = system ("/sbin/modprobe ppp_generic");

	connection = nm_act_request_get_connection (req);
	g_assert (connection);

	s_ppp = nm_connection_get_setting_ppp (connection);
	if (!s_ppp) {


		s_ppp = NM_SETTING_PPP (nm_setting_ppp_new ());
		s_ppp_created = TRUE;
	}

	pppoe_setting = nm_connection_get_setting_pppoe (connection);
	if (pppoe_setting)
		pppoe_fill_defaults (s_ppp);

	adsl_setting = (NMSettingAdsl *) nm_connection_get_setting (connection, NM_TYPE_SETTING_ADSL);

	ppp_cmd = create_pppd_cmd_line (manager, s_ppp, pppoe_setting, adsl_setting, ppp_name, err);
	if (!ppp_cmd)
		goto out;

	g_ptr_array_add (ppp_cmd->array, NULL);

	nm_log_info (LOGD_PPP, "starting PPP connection");

	cmd_str = nm_cmd_line_to_str (ppp_cmd);
	nm_log_dbg (LOGD_PPP, "command line: %s", cmd_str);
	g_free (cmd_str);

	priv->pid = 0;
	if (!g_spawn_async (NULL, (char **) ppp_cmd->array->pdata, NULL,
					G_SPAWN_DO_NOT_REAP_CHILD,
					pppd_child_setup,
					NULL, &priv->pid, err)) {
		goto out;
	}

	nm_log_info (LOGD_PPP, "pppd started with pid %d", priv->pid);

	priv->ppp_watch_id = g_child_watch_add (priv->pid, (GChildWatchFunc) ppp_watch_cb, manager);
	priv->ppp_timeout_handler = g_timeout_add_seconds (timeout_secs, pppd_timed_out, manager);
	priv->act_req = g_object_ref (req);

 out:
	if (s_ppp_created)
		g_object_unref (s_ppp);

	if (ppp_cmd)
		nm_cmd_line_destroy (ppp_cmd);

	return priv->pid > 0;
}
