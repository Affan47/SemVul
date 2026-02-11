CheckForUnevenTeams ()
{
	int i, onteam1 = 0, onteam2 = 0;
	edict_t *e;


	if (num_teams > 2)
		return;

	for (i = 1; i <= maxclients->value; i++)
	{
		e = g_edicts + i;
		if (e->inuse)
		{
			if (e->client->resp.team == TEAM1)
				onteam1++;
			else if (e->client->resp.team == TEAM2)
				onteam2++;
		}
	}
	if (onteam1 > onteam2)
		UnevenTeamsMsg (TEAM1, onteam1 - onteam2, teams[TEAM2].name);
	else if (onteam2 > onteam1)
		UnevenTeamsMsg (TEAM2, onteam2 - onteam1, teams[TEAM1].name);
}
