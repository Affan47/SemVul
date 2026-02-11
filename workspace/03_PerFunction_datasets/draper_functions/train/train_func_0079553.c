gm_mcp_session_package_class_for_each(GmPackageClassFunc func,
		gpointer user_data) {
	GmMcpSessionClass *klass = g_type_class_peek(GM_TYPE_MCP_SESSION);
	GList *item;
	GmMcpPackageClass *package_klass;

	for (item = klass->available_packages; item; item = item->next) {
		package_klass = GM_MCP_PACKAGE_CLASS(item->data);

		if (func(package_klass, user_data)) {
			return package_klass;
		}
	}

	return NULL;
}
