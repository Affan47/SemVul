M_UnbindCommand (const char *command)
{
	int		j;
	int		l;
	char	*b;

	l = strlen(command);

	for (j=0 ; j<256 ; j++)
	{
		b = keybindings[j];
		if (!b)

			continue;
		if (!strncmp (b, command, l) )
			Key_SetBinding (j, "");
	}
}
