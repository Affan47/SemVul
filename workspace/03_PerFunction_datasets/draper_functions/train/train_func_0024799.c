Cmd_List_f (void)
{
	cmd_function_t  *cmd;
    const char *filter = NULL;
	int		i, total = 0, matching = 0;
	cmd_function_t	**sortedList;

    if (Cmd_Argc() > 1)
	    filter = Cmd_Argv(1);

	for (cmd = cmd_functions; cmd; cmd = cmd->next, total++) {
        if (filter && !Com_WildCmp(filter, cmd->name) && !strstr(cmd->name, filter))
			continue;
		matching++;
	}

	if(!matching) {
		Com_Printf("%i cmds found (%i total cmds)\n", matching, total);
		return;
	}

	sortedList = Z_TagMalloc (matching * sizeof(cmd_function_t *), TAG_CMD);

	for (matching = 0, cmd = cmd_functions; cmd; cmd = cmd->next) {
        if (filter && !Com_WildCmp(filter, cmd->name) && !strstr(cmd->name, filter))
			continue;
		sortedList[matching++] = cmd;
	}

	qsort(sortedList, matching, sizeof(sortedList[0]), (int (*)(const void *, const void *))CmdSort);

	for (i = 0; i < matching; i++)
	{
		cmd = sortedList[i];
        Com_Printf("%s\n", cmd->name);
    }

    if (filter)
		Com_Printf("%i cmds found (%i total cmds)\n", matching, total);
    else
		Com_Printf("%i cmds\n", matching);

	Z_Free (sortedList);
}
