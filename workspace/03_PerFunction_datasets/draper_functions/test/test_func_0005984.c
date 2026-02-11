UPNP_AddPortMapping(const char * controlURL, const char * servicetype,
                    const char * extPort,
					const char * inPort,
					const char * inClient,
					const char * desc,
					const char * proto,
                    const char * remoteHost)
{
	struct UPNParg * AddPortMappingArgs;
	char buffer[4096];
	int bufsize = 4096;
	struct NameValueParserData pdata;
	const char * resVal;
	int ret;

	if(!inPort || !inClient || !proto || !extPort)
		return UPNPCOMMAND_INVALID_ARGS;

	AddPortMappingArgs = calloc(9, sizeof(struct UPNParg));
	AddPortMappingArgs[0].elt = "NewRemoteHost";
	AddPortMappingArgs[0].val = remoteHost;
	AddPortMappingArgs[1].elt = "NewExternalPort";
	AddPortMappingArgs[1].val = extPort;
	AddPortMappingArgs[2].elt = "NewProtocol";
	AddPortMappingArgs[2].val = proto;
	AddPortMappingArgs[3].elt = "NewInternalPort";
	AddPortMappingArgs[3].val = inPort;
	AddPortMappingArgs[4].elt = "NewInternalClient";
	AddPortMappingArgs[4].val = inClient;
	AddPortMappingArgs[5].elt = "NewEnabled";
	AddPortMappingArgs[5].val = "1";
	AddPortMappingArgs[6].elt = "NewPortMappingDescription";
	AddPortMappingArgs[6].val = desc?desc:"libminiupnpc";
	AddPortMappingArgs[7].elt = "NewLeaseDuration";
	AddPortMappingArgs[7].val = "0";
	if(simpleUPnPcommand(-1, controlURL, servicetype, "AddPortMapping", AddPortMappingArgs, buffer, &bufsize) < 0) {
		free(AddPortMappingArgs);
		return UPNPCOMMAND_HTTP_ERROR;
	}


	ParseNameValue(buffer, bufsize, &pdata);
	resVal = GetValueFromNameValueList(&pdata, "errorCode");
	if(resVal) {

		ret = UPNPCOMMAND_UNKNOWN_ERROR;
		sscanf(resVal, "%d", &ret);
	} else {
		ret = UPNPCOMMAND_SUCCESS;
	}
	ClearNameValueList(&pdata);
	free(AddPortMappingArgs);
	return ret;
}
