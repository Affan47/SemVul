SV_StatusString (void)
{
	char	player[1024];
	static char	status[MAX_MSGLEN - 16];
	int		i;
	client_t	*cl;
	int		statusLength;
	int		playerLength;

	strcpy (status, Cvar_Serverinfo());
	strcat (status, "\n");
	statusLength = strlen(status);

	for (i=0 ; i<maxclients->integer ; i++)
	{
		cl = &svs.clients[i];
		if (cl->state == cs_connected || cl->state == cs_spawned )
		{
			Com_sprintf (player, sizeof(player), "%i %i \"%s\"\n",
				cl->edict->client->ps.stats[STAT_FRAGS], cl->ping, cl->name);
			playerLength = strlen(player);
			if (statusLength + playerLength >= sizeof(status) )
				break;
			strcpy (status + statusLength, player);
			statusLength += playerLength;
		}
	}

	return status;
}
