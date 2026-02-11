gmlc_misc_config_update_server (GmlcMiscConfig * pGmlcMscCfg, const gchar * oldname, const gchar * name, const gchar * host, const gint port, const gchar * login, const gchar * passwd, const gchar * dbAllowedList, const gchar * localSock, const gboolean read_only, const gboolean write_warning) {
	GmlcMysqlServer * pGmlcMysqlSrv;

	pGmlcMysqlSrv = gmlc_misc_config_get_server(pGmlcMscCfg, oldname);

	if (pGmlcMysqlSrv != NULL) {

		g_object_set(pGmlcMysqlSrv,
			"name", name,
			"hostname", host,
			"port", port,
			"login", login,
			"password", passwd,
			"allowed_dbs", dbAllowedList,
			"local_socket", localSock,
			"read_only", read_only,
			"write_warning", write_warning,
			NULL);

		return TRUE;
	}

	return FALSE;
}
