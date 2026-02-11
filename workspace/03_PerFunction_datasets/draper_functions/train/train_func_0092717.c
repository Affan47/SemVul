gm_mcp_mud_moo_simpleedit_handle_multi(GmMcpPackage *package,
		gchar const *data_tag, gchar const *key, gchar const *value,
		GList *all_values) {
	GmEditor *editor;
	GmMcpMudMooSimpleedit *simpleedit = GM_MCP_MUD_MOO_SIMPLEEDIT(package);

	if (key) {
		return FALSE;
	} else {

		editor = gm_editor_new_mcp(simpleedit->priv->name,
				simpleedit->priv->ref, simpleedit->priv->type, all_values);

		gm_mcp_mud_moo_simpleedit_add_editor(simpleedit, editor);
		gm_world_add_editor(GM_MCP_SESSION_WORLD(GM_MCP_PACKAGE_SESSION(
				package)), editor);
	}

	return TRUE;
}
