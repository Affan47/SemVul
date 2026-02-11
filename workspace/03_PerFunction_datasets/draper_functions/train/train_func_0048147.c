Cmd_Echo_f (void)
{
	int		i;

	for (i=1 ; i<Cmd_Argc() ; i++)
		Com_Printf ("%s ",Cmd_Argv(i));
	Com_Printf ("\n");
}
