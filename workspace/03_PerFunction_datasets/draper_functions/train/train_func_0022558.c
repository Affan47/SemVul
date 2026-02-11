DisplayInfos(struct UPNPUrls * urls,
                         struct IGDdatas * data)
{
	char externalIPAddress[16];
	char connectionType[64];
	char status[64];
	char lastconnerr[64];
	unsigned int uptime;
	unsigned int brUp, brDown;
	time_t timenow, timestarted;
	int r;
	UPNP_GetConnectionTypeInfo(urls->controlURL,
	                           data->first.servicetype,
							   connectionType);
	if(connectionType[0])
		printf("Connection Type : %s\n", connectionType);
	else
		printf("GetConnectionTypeInfo failed.\n");
	UPNP_GetStatusInfo(urls->controlURL, data->first.servicetype,
	                   status, &uptime, lastconnerr);
	printf("Status : %s, uptime=%us, LastConnectionError : %s\n",
	       status, uptime, lastconnerr);
	timenow = time(NULL);
	timestarted = timenow - uptime;
	printf("  Time started : %s", ctime(&timestarted));
	UPNP_GetLinkLayerMaxBitRates(urls->controlURL_CIF, data->CIF.servicetype,
			&brDown, &brUp);
	printf("MaxBitRateDown : %u bps   MaxBitRateUp %u bps\n", brDown, brUp);
	r = UPNP_GetExternalIPAddress(urls->controlURL,
	                          data->first.servicetype,
							  externalIPAddress);
	if(r != UPNPCOMMAND_SUCCESS)
		printf("GetExternalIPAddress() returned %d\n", r);
	if(externalIPAddress[0])
		printf("ExternalIPAddress = %s\n", externalIPAddress);
	else
		printf("GetExternalIPAddress failed.\n");
}
