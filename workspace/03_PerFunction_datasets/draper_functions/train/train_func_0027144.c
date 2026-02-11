xmlrpc_config_ready(void *vptr)
{


	handle_xmlrpc.path = xmlrpc_config.path;

	if (handle_xmlrpc.handler != NULL)
	{
		if (mowgli_node_find(&handle_xmlrpc, httpd_path_handlers))
			return;

		mowgli_node_add(&handle_xmlrpc, mowgli_node_create(), httpd_path_handlers);
	}
	else
		slog(LG_ERROR, "xmlrpc_config_ready(): xmlrpc {} block missing or invalid");
}
