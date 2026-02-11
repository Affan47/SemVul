nutclient_has_device_command(NUTCLIENT_t client, const char* dev, const char* cmd)
{
	if(client)
	{
		nut::Client* cl = (nut::Client*)client;
		if(cl)
		{
			try
			{
				return cl->hasDeviceCommand(dev, cmd)?1:0;
			}
			catch(...){}
		}
	}
	return 0;
}
