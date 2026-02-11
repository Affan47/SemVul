UPNP_GetStatusInfo(const char * controlURL,
				const char * servicetype,
				char * status,
				unsigned int * uptime,
				char * lastconnerror)
{
	struct NameValueParserData pdata;
	char buffer[4096];
	int bufsize = 4096;
	char * p;
	char * up;
	char * err;
	int ret = UPNPCOMMAND_UNKNOWN_ERROR;

	if(!status && !uptime)
		return UPNPCOMMAND_INVALID_ARGS;

	if(simpleUPnPcommand(-1, controlURL, servicetype, "GetStatusInfo", 0, buffer, &bufsize) < 0) {
		return UPNPCOMMAND_HTTP_ERROR;
	}
	ParseNameValue(buffer, bufsize, &pdata);

	up = GetValueFromNameValueList(&pdata, "NewUptime");
	p = GetValueFromNameValueList(&pdata, "NewConnectionStatus");
	err = GetValueFromNameValueList(&pdata, "NewLastConnectionError");
	if(p && up)
	  ret = UPNPCOMMAND_SUCCESS;

	if(status) {
		if(p){
			strncpy(status, p, 64 );
			status[63] = '\0';
		}else
			status[0]= '\0';
	}

	if(uptime) {
		if(up)
			sscanf(up,"%u",uptime);
		else
			uptime = 0;
	}

	if(lastconnerror) {
		if(err) {
			strncpy(lastconnerror, err, 64 );
			lastconnerror[63] = '\0';
		} else
			lastconnerror[0] = '\0';
	}

	p = GetValueFromNameValueList(&pdata, "errorCode");
	if(p) {
		ret = UPNPCOMMAND_UNKNOWN_ERROR;
		sscanf(p, "%d", &ret);
	}
	ClearNameValueList(&pdata);
	return ret;
}
