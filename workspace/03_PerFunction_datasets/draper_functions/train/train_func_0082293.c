on_menu_session_commit (GtkMenuItem *mi, gpointer data)
{
	GSQL_TRACE_FUNC;
	GSQLSession *session = NULL;

	session = gsql_session_get_active ();

	g_return_if_fail (GSQL_IS_SESSION (session));

	g_signal_emit_by_name (G_OBJECT (session), "commit");

}
