CL_Skins_f (void)
{
	int		i;

	for (i=0 ; i<MAX_CLIENTS ; i++)
	{
		if (!cl.configstrings[CS_PLAYERSKINS+i][0])
			continue;
		Com_Printf ("client %i: %s\n", i, cl.configstrings[CS_PLAYERSKINS+i]);
		SCR_UpdateScreen ();
		Sys_SendKeyEvents ();
		CL_ParseClientinfo (i);
	}
}
