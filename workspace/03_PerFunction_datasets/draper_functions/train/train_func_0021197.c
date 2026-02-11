SV_Shutdown (char *finalmsg, qboolean reconnect)
{
	extern void Con_Clear_f (void);

	if (svs.clients)
		SV_FinalMessage (finalmsg, reconnect);

	Master_Shutdown ();
	SV_ShutdownGameProgs ();


	if (sv.demofile)
		fclose (sv.demofile);
	memset (&sv, 0, sizeof(sv));
	Com_SetServerState (sv.state);


	if (svs.clients)
		Z_Free (svs.clients);
	if (svs.client_entities)
		Z_Free (svs.client_entities);
	if (svs.demofile)
		fclose (svs.demofile);
	memset (&svs, 0, sizeof(svs));
}
