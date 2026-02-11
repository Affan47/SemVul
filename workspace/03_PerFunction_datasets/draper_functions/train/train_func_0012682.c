Cbuf_AddEarlyCommands (qboolean clear)
{
	int		i;
	char	*s;

	for (i = 0; i < COM_Argc(); i++)
	{
		s = COM_Argv(i);
		if (strcmp (s, "+set"))
			continue;
		Cbuf_AddText (va("set %s %s\n", COM_Argv(i+1), COM_Argv(i+2)));
		if (clear)
		{
			COM_ClearArgv(i);
			COM_ClearArgv(i+1);
			COM_ClearArgv(i+2);
		}
		i+=2;
	}
}
