Master_Shutdown (void)
{
	int			i;


	if (!dedicated->integer)
		return;


	if (!public_server || !public_server->integer)
		return;


	for (i=0 ; i<MAX_MASTERS ; i++)
		if (master_adr[i].port)
		{
			if (i > 0)
				Com_Printf ("Sending heartbeat to %s\n", NET_AdrToString (&master_adr[i]));
			Netchan_OutOfBandPrint (NS_SERVER, &master_adr[i], "shutdown");
		}
}
