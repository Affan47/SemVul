GetWeaponName(edict_t * ent, char *buf)
{
	if (ent->client->pers.weapon) {
		strcpy(buf, ent->client->pers.weapon->pickup_name);
		return;
	}

	strcpy(buf, "No Weapon");
}
