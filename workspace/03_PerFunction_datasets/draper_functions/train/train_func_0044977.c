Cmd_Votekicknum_f (edict_t * ent, char *argument)
{
	int i;
	edict_t *target;

	if (!*argument)
	{
		gi.cprintf (ent, PRINT_HIGH, "\nUse votekicknum <playernumber>.\n");
		return;
	}

	i = atoi (argument);

	if(i < 1 || i > game.maxclients)
	{
		gi.cprintf (ent, PRINT_MEDIUM, "\nUsed votekicknum with illegal number.\n");
		return;
	}

	target = &g_edicts[i];
	if (target && target->client && target != ent && target->inuse)
		_SetKickVote (ent, target);
	else
		gi.cprintf (ent, PRINT_HIGH, "\nUse kicklist to see who can be kicked.\n");

}
