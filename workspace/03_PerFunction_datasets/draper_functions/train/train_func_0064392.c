conf_end_connect(struct TopConf *tc)
{
	if(EmptyString(yy_server->name))
	{
		conf_report_error("Ignoring connect block -- missing name.");
		return 0;
	}

	if(ServerInfo.name != NULL && !irccmp(ServerInfo.name, yy_server->name))
	{
		conf_report_error("Ignoring connect block for %s -- name is equal to my own name.",
				yy_server->name);
		return 0;
	}

	if((EmptyString(yy_server->passwd) || EmptyString(yy_server->spasswd)) && EmptyString(yy_server->certfp))
	{
		conf_report_error("Ignoring connect block for %s -- no fingerprint or password credentials provided.",
					yy_server->name);
		return 0;
	}

	if(EmptyString(yy_server->host))
	{
		conf_report_error("Ignoring connect block for %s -- missing host.",
					yy_server->name);
		return 0;
	}

#ifndef HAVE_LIBZ
	if(ServerConfCompressed(yy_server))
	{
		conf_report_error("Ignoring connect::flags::compressed -- zlib not available.");
		yy_server->flags &= ~SERVER_COMPRESSED;
	}
#endif

	add_server_conf(yy_server);
	rb_dlinkAdd(yy_server, &yy_server->node, &server_conf_list);

	yy_server = NULL;
	return 0;
}
