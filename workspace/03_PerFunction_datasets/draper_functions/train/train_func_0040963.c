command_version(struct command_base* cbase, struct hub_user* user, struct hub_command* cmd)
{
	struct cbuffer* buf;
	if (cbase->hub->config->show_banner_sys_info)
		buf = cbuf_create_const("Powered by " PRODUCT_STRING " on " OPSYS "/" CPUINFO);
	else
		buf = cbuf_create_const("Powered by " PRODUCT_STRING);
	return command_status(cbase, user, cmd, buf);
}
