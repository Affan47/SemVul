CL_Highlight_f( void )
{
	highlight_t *entry;
	const char *s;
	int color = -1, tLen;

	if (Cmd_Argc() != 2 && Cmd_Argc() != 3)
	{
		Com_Printf("Usage: %s <text> [color]\n", Cmd_Argv(0));
		Com_Printf("Current text highlights:\n");
		Com_Printf("------------------------\n");
		for(entry = cl_highlights; entry; entry = entry->next)
			Com_Printf("%s\n", entry->text);

		return;
	}

	s = Cmd_Argv(1);
	tLen = strlen(s);
	if(tLen < 3) {
		Com_Printf("Text is too short.\n");
		return;
	}

	if(Cmd_Argc() > 2)
		color = atoi(Cmd_Argv(2))&7;

	for(entry = cl_highlights; entry; entry = entry->next) {
		if(!strcmp(entry->text, s))
		{
			if(entry->color != color)
				entry->color = color;


			return;
		}
	}

	entry = Z_TagMalloc(sizeof(highlight_t) + tLen+1, TAG_CL_IGNORE);
	entry->text = (char *)((byte *)entry + sizeof(highlight_t));
	strcpy(entry->text, s);
	entry->color = color;
	entry->next = cl_highlights;
	cl_highlights = entry;
}
