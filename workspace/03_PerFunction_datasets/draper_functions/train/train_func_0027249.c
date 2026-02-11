initprotocolplugin(struct protocolplugininfo &protocolplugininfo,
	class Options &options, bool debugmode)
{
	if (options["icq_protocol"] != "on") return false;

	localdebugmode = debugmode;

	protocolplugininfo.pluginname = PLUGIN_NAME;
	protocolplugininfo.protocolname = PROTOCOL_NAME;
#ifdef HAVE_SSL
	if (options["icq_ssl"] == "on")
	{
		syslog(LOG_INFO, PROTOCOL_NAME ": Monitoring SSL");

		protocolplugininfo.sslport = htons(PROTOCOL_PORT);
	}
	else
		protocolplugininfo.port = htons(PROTOCOL_PORT);
#else
	protocolplugininfo.port = htons(PROTOCOL_PORT);
#endif


	iconv_utf16be_utf8 = iconv_open("UTF-8", "UTF-16BE");
	if (iconv_utf16be_utf8 == (iconv_t) -1)
	{
		syslog(LOG_ERR, PROTOCOL_NAME ": Error: iconv_open failed: %s", strerror(errno));
		return false;
	}


	switch (fork())
	{

		case -1:
			syslog(LOG_ERR, PROTOCOL_NAME ": Error: Fork failed: %s", strerror(errno));
			return false;


		case 0:
			cookiemonster();
			debugprint(localdebugmode,  PROTOCOL_NAME ": Error: We should not come here");
			exit(0);


		default:
			break;
	}

	if (options["icq_trace"] == "on") tracing = true;
	if (options["icq_trace_error"] == "on") tracingerror = true;

	return true;
}
