SV_DemoMap_f (void)
{
	char	demoName[MAX_QPATH];

	if (Cmd_Argc() != 2)
	{
		Com_Printf ("USAGE: demomap <demoname>\n");
		return;
	}

	if(strlen(Cmd_Argv(1)) >= sizeof(demoName)-1)
	{
		Com_Printf("Demomap: Demo name is too long\n");
		return;
	}

	Q_strncpyz(demoName, Cmd_Argv(1), sizeof(demoName));
	COM_DefaultExtension(demoName, sizeof(demoName), ".dm2");

	SV_Map (true, demoName, false );
}
