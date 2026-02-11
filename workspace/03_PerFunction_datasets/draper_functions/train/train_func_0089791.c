SV_InitGame (void)
{
	int		i;
	edict_t	*ent;
	char	idmaster[32];

	if (svs.initialized)
	{

		SV_Shutdown ("Server restarted\n", true);
	}
	else
	{

		CL_Drop ();
		SCR_BeginLoadingPlaque ();
	}


	Cvar_GetLatchedVars (CVAR_LATCH);

	CL_LocalConnect();

	svs.initialized = true;

	if (Cvar_VariableValue ("coop") && Cvar_VariableValue ("deathmatch"))
	{
		Com_Printf("Deathmatch and Coop both set, disabling Coop\n");
		Cvar_FullSet ("coop", "0",  CVAR_SERVERINFO | CVAR_LATCH);
	}


	if (dedicated->integer)
	{
		if (!Cvar_VariableValue ("coop"))
			Cvar_FullSet ("deathmatch", "1",  CVAR_SERVERINFO | CVAR_LATCH);
	}


	if (Cvar_VariableValue ("deathmatch"))
	{
		if (maxclients->integer <= 1)
			Cvar_FullSet ("maxclients", "8", CVAR_SERVERINFO | CVAR_LATCH);
		else if (maxclients->integer > MAX_CLIENTS)
			Cvar_FullSet ("maxclients", va("%i", MAX_CLIENTS), CVAR_SERVERINFO | CVAR_LATCH);
	}
	else if (Cvar_VariableValue ("coop"))
	{
		if (maxclients->integer <= 1 || maxclients->integer > 4)
			Cvar_FullSet ("maxclients", "4", CVAR_SERVERINFO | CVAR_LATCH);
#ifdef COPYPROTECT
		if (!sv.attractloop && !dedicated->integer)
			Sys_CopyProtect ();
#endif
	}
	else
	{
		Cvar_FullSet ("maxclients", "1", CVAR_SERVERINFO | CVAR_LATCH);
#ifdef COPYPROTECT
		if (!sv.attractloop)
			Sys_CopyProtect ();
#endif
	}

	svs.spawncount = rand();
	svs.clients = Z_TagMalloc (sizeof(client_t)*maxclients->integer, TAG_CLIENTS);
	svs.num_client_entities = maxclients->integer*UPDATE_BACKUP*64;
	svs.client_entities = Z_TagMalloc (sizeof(entity_state_t)*svs.num_client_entities, TAG_CL_ENTS);

	memset (svs.clients, 0, sizeof(client_t)*maxclients->integer);
	memset (svs.client_entities, 0, sizeof(entity_state_t)*svs.num_client_entities);


	if (maxclients->integer > 1)
		NET_Config(NET_SERVER);


	svs.last_heartbeat = -99999;
	Com_sprintf(idmaster, sizeof(idmaster), "192.246.40.37:%i", PORT_MASTER);
	NET_StringToAdr (idmaster, &master_adr[0]);


	SV_InitGameProgs ();
	for (i=0 ; i<maxclients->integer ; i++)
	{
		ent = EDICT_NUM(i+1);
		ent->s.number = i+1;
		svs.clients[i].edict = ent;
		memset (&svs.clients[i].lastcmd, 0, sizeof(svs.clients[i].lastcmd));
	}
}
