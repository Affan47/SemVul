Cmd_Lens_f(edict_t * ent)
{
	int nArg;
	char args[8];

	if (ent->client->curr_weap != SNIPER_NUM)
		return;

	nArg = atoi(gi.args());

	if (nArg == 0) {
		Q_strncpyz(args, gi.args(), sizeof(args));

		if (Q_stricmp(args, "in") == 0)
			_ZoomIn(ent, false);
		else if (Q_stricmp(args, "out") == 0)
			_ZoomOut(ent, false);
		else
			_ZoomIn(ent, true);

		if(!ent->client->desired_zoom)
			return;
	}
	else if ((nArg == 1) || (!(nArg % 2) && (nArg <= 6)))
		ent->client->desired_zoom = nArg;
	else
		_ZoomIn(ent, true);

	if(ent->client->weapon_attempts > 0)
		return;


	ent->client->weapon_attempts++;
	if (ent->client->weapon_attempts == 1)
		Cmd_Weapon_f(ent);
}
