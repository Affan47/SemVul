SVC_Info (void)
{
	char	string[64];
	int		i, count;
	int		version;
	client_t	*cl;

	if (maxclients->integer == 1)
		return;

	version = atoi (Cmd_Argv(1));

	if (version != PROTOCOL_VERSION) {
		Com_sprintf (string, sizeof(string), "%s: wrong version\n", hostname->string, sizeof(string));


		return;
	}
	else
	{
		count = 0;
		for (i=0 ; i<maxclients->integer ; i++)
			if (svs.clients[i].state >= cs_connected)
				count++;


		for (i=0 ; i<maxclients->integer ; i++)
		{
			cl = &svs.clients[i];
			if(cl->edict->client->ps.botnum > 0)
			{
				count += cl->edict->client->ps.botnum;
				break;
			}
		}


		Com_sprintf (string, sizeof(string), "%16s %8s %2i/%2i\n", hostname->string, sv.name, count, maxclients->integer);
	}

	Netchan_OutOfBandPrint (NS_SERVER, net_from, "info\n%s", string);
}
