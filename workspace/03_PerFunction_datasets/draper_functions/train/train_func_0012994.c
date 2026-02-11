Cmd_New_Weapon_f(edict_t * ent)
{
	ent->client->weapon_attempts++;
	if (ent->client->weapon_attempts == 1)
		Cmd_Weapon_f(ent);
}
