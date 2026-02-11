ExitLevel (void)
{
	int i;
	edict_t *ent;
	char command[256];

	Com_sprintf (command, sizeof (command), "gamemap \"%s\"\n", level.changemap);
	gi.AddCommandString (command);
	level.changemap = NULL;
	level.exitintermission = 0;
	level.intermissiontime = 0;
	ClientEndServerFrames ();


	for (i = 0; i < maxclients->value; i++)
	{
		ent = g_edicts + 1 + i;
		if (!ent->inuse)
			continue;
		if (ent->health > ent->client->pers.max_health)
			ent->health = ent->client->pers.max_health;
	}


	if (teamplay->value)
	{
		for(i=TEAM1; i<TEAM_TOP; i++)
		{
			teams[i].score = 0;

			gi.cvar_forceset(teams[i].teamscore->name, "0");
		}
	}

	if (ctf->value)
	{
		CTFInit ();
	}
}
