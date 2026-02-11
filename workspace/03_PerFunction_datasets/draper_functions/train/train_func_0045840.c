gm_mcp_session_create_package(GmMcpSession *session, GmMcpPackageClass *klass,
		gdouble version) {
	GmMcpPackage *package;

	if (!klass) {
		return NULL;
	}

	if (!gm_mcp_session_has_package_of_class(session, klass)) {
		package = g_object_new(G_TYPE_FROM_CLASS(G_OBJECT_CLASS(klass)), NULL);

		gm_mcp_package_set_session(package, G_OBJECT(session));
		gm_mcp_package_set_version(package, version);

	    session->priv->packages = g_list_append(session->priv->packages,
	    		package);

	    g_signal_emit(session, gm_mcp_session_signals[PACKAGE_CREATED],
	    		0, G_OBJECT(package));
	    return package;
	} else {
		gm_debug_msg(DEBUG_MCP, "GmMcpSession.CreatePackage: package (%s) is "
				"already registered for %s", klass->name,
				gm_options_get(gm_world_options(session->priv->world), "name"));
		return NULL;
	}
}
