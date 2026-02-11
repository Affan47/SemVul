CheckForWinner ()
{
	int players[TEAM_TOP] = {0}, i;
	edict_t *ent;

	if(ctf->value || teamdm->value)
		return WINNER_NONE;

	for (i = 0; i < game.maxclients; i++)
	{
		ent = &g_edicts[1 + i];
		if (!ent->inuse || game.clients[i].resp.team == NOTEAM)
			continue;
		if (ent->solid != SOLID_NOT)
			players[game.clients[i].resp.team]++;
	}

	if (players[1] && players[2])
		return WINNER_NONE;

	if (use_3teams->value && ((players[1] && players[3]) || (players[2] && players[3])))
		return WINNER_NONE;

	for(i=TEAM1; i<=teamCount; i++)
		if(players[i])
			return i;

	return WINNER_TIE;

}
