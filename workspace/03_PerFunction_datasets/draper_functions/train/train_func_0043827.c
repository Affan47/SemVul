gm_mcp_awns_status_create_view(GmMcpPackage *package, GObject *parent) {
	GmMcpAwnsStatusView *status_view;

	if (GM_IS_WORLD_VIEW(parent)) {
		status_view = g_new0(GmMcpAwnsStatusView, 1);
		status_view->package = GM_MCP_AWNS_STATUS(package);
		status_view->view = GM_WORLD_VIEW(parent);

		g_signal_connect(package, "status_changed",
				G_CALLBACK(on_gm_mcp_awns_status_view_status_changed),
				status_view);
		g_object_weak_ref(G_OBJECT(package),
				on_gm_mcp_awns_status_view_weak_notify, status_view);

	}
}
