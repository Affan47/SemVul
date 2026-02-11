UPNPIGD_IsConnected(struct UPNPUrls * urls, struct IGDdatas * data)
{
	char status[64];
	unsigned int uptime;
	status[0] = '\0';
	UPNP_GetStatusInfo(urls->controlURL, data->first.servicetype,
	                   status, &uptime, NULL);
	if(0 == strcmp("Connected", status))
	{
		return 1;
	}
	else
		return 0;
}
