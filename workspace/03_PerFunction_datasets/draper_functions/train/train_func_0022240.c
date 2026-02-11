Team_f (edict_t * ent)
{
	char *t;
	int desired_team = NOTEAM;
	char team[24];


	if (use_tourney->value)
	{
		gi.cprintf (ent, PRINT_MEDIUM,
		"Currently running tourney mod, team selection is disabled.");
		return;
	}

	Q_strncpyz(team, gi.args(), sizeof(team));
	t = team;

	if (!*t)
	{
		if (ctf->value)
		{
			gi.cprintf (ent, PRINT_HIGH, "You are on %s.\n",
			CTFTeamName (ent->client->resp.team));
			return;
		}
		else
		{
			gi.cprintf (ent, PRINT_HIGH, "You are on %s.\n",
			TeamName (ent->client->resp.team));
			return;
		}
	}

	if ((int)(realLtime*10.0f) < (ent->client->resp.joined_team + 50))
	{
		gi.cprintf (ent, PRINT_HIGH, "You must wait 5 seconds before changing teams again.\n");
		return;
	}

	if (Q_stricmp (t, "none") == 0)
	{
		if (ent->client->resp.team == NOTEAM)
			gi.cprintf (ent, PRINT_HIGH, "You're not on a team.\n");
		else
			LeaveTeam (ent);

		return;
	}

	if (Q_stricmp (t, "1") == 0)
		desired_team = TEAM1;
	else if (Q_stricmp (t, "2") == 0)
		desired_team = TEAM2;
	else if (Q_stricmp (t, teams[TEAM1].name) == 0)
		desired_team = TEAM1;
	else if (Q_stricmp (t, teams[TEAM2].name) == 0)
		desired_team = TEAM2;
	else if (use_3teams->value)
	{
		if (Q_stricmp (t, "3") == 0)
			desired_team = TEAM3;
		else if (Q_stricmp (t, teams[TEAM3].name) == 0)
			desired_team = TEAM3;
	}
	else if (ctf->value)
	{
		if (Q_stricmp (t, "red") == 0)
			desired_team = TEAM1;
		else if (Q_stricmp (t, "blue") == 0)
			desired_team = TEAM2;
	}

	if(desired_team == NOTEAM)
	{
		gi.cprintf (ent, PRINT_HIGH, "Unknown team %s.\n", t);
		return;
	}

	if (ent->client->resp.team == desired_team)
	{
		gi.cprintf (ent, PRINT_HIGH, "You are already on %s.\n",
		TeamName (ent->client->resp.team));
		return;
	}

	JoinTeam (ent, desired_team, 1);
}
