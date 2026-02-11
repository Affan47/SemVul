Cmd_Use_f (edict_t * ent)
{
	gitem_t *it;
	char *s;

	s = gi.args ();


	if (Q_stricmp (s, "special") == 0)
	{
		ReadySpecialWeapon (ent);
		return;
	}


	if (!Q_stricmp (s, "blaster") || !Q_stricmp (s, "mark 23 pistol"))
		s = MK23_NAME;
	else if (!Q_stricmp (s, "A 2nd pistol") || !Q_stricmp (s, "railgun"))
		s = DUAL_NAME;
	else if (!Q_stricmp (s, "shotgun"))
		s = M3_NAME;
	else if (!Q_stricmp (s, "machinegun"))
		s = HC_NAME;
	else if (!Q_stricmp (s, "super shotgun"))
		s = MP5_NAME;
	else if (!Q_stricmp (s, "chaingun"))
		s = SNIPER_NAME;
	else if (!Q_stricmp (s, "bfg10k"))
		s = KNIFE_NAME;

	else if (!Q_stricmp (s, "throwing combat knife"))
	{

		if (l4d->value && ent->client->resp.team == TEAM1)
			return;

		if (ent->client->curr_weap != KNIFE_NUM)
		{
			ent->client->resp.knife_mode = 1;
		}
		else
		{

				Cmd_New_Weapon_f (ent);
		}
		s = KNIFE_NAME;
	}
	else if (!Q_stricmp (s, "slashing combat knife"))
	{
		if (ent->client->curr_weap != KNIFE_NUM)
		{
			ent->client->resp.knife_mode = 0;
		}
		else
		{

				Cmd_New_Weapon_f (ent);
		}
		s = KNIFE_NAME;
	}
	else if (!Q_stricmp (s, "grenade launcher"))
		s = M4_NAME;
	else if (!Q_stricmp (s, "grenades"))
		s = GRENADE_NAME;

	it = FindItem (s);


	if (!it || (ent->solid == SOLID_NOT && ent->deadflag != DEAD_DEAD))

	{
		gi.cprintf (ent, PRINT_HIGH, "Unknown item: %s\n", s);
		return;
	}

	if (!it->use)
	{
		gi.cprintf (ent, PRINT_HIGH, "Item is not usable.\n");
		return;
	}

	if (!ent->client->pers.inventory[ITEM_INDEX (it)])
	{
		gi.cprintf (ent, PRINT_HIGH, "Out of item: %s\n", s);
		return;
	}


	ent->client->autoreloading = false;


	it->use (ent, it);
}
