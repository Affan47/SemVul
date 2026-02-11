uniq(struct cmdnames *cmds)
{
	int i, j;

	if (!cmds->cnt)
		return;

	for (i = j = 1; i < cmds->cnt; i++)
		if (strcmp(cmds->names[i]->name, cmds->names[i-1]->name))
			cmds->names[j++] = cmds->names[i];

	cmds->cnt = j;
}
