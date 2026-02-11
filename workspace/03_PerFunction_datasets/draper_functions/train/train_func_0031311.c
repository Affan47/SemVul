_modinit(module_t *m)
{
	MODULE_USE_SYMBOL(httpd_path_handlers, "misc/httpd", "httpd_path_handlers");

	hook_add_event("config_ready");
	hook_add_config_ready(xmlrpc_config_ready);

	xmlrpc_config.path = sstrdup("/xmlrpc");

	add_subblock_top_conf("XMLRPC", &conf_xmlrpc_table);
	add_dupstr_conf_item("PATH", &conf_xmlrpc_table, 0, &xmlrpc_config.path, NULL);

	xmlrpc_set_buffer(dump_buffer);
	xmlrpc_set_options(XMLRPC_HTTP_HEADER, XMLRPC_OFF);
	xmlrpc_register_method("atheme.login", xmlrpcmethod_login);
	xmlrpc_register_method("atheme.logout", xmlrpcmethod_logout);
	xmlrpc_register_method("atheme.command", xmlrpcmethod_command);
	xmlrpc_register_method("atheme.privset", xmlrpcmethod_privset);
}
