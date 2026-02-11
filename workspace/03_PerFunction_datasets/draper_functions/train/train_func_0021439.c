on_session_load (AnjutaShell *shell, AnjutaSessionPhase phase, AnjutaSession *session, ExprWatch *ew)
{
	GList *list;

	if (phase != ANJUTA_SESSION_PHASE_NORMAL)
		return;

	debug_tree_remove_all (ew->debug_tree);
	list = anjuta_session_get_string_list (session, "Debugger", "Watch");
	if (list != NULL)
		debug_tree_add_full_watch_list (ew->debug_tree, list);
}
