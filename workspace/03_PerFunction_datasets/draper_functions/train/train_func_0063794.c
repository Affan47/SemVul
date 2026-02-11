pgsql_session_workspace_info (GSQLSession *session, gchar *msg) {
	GSQLWorkspace *workspace = NULL;
	g_return_if_fail ( GSQL_IS_SESSION (session) );

	workspace = gsql_session_get_workspace (session);
	g_return_if_fail (GSQL_IS_WORKSPACE(workspace));

	gsql_message_add (workspace, GSQL_MESSAGE_NOTICE, msg);
}
