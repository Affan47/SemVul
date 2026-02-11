GetNearbyTeammates(edict_t * self, char *buf)
{
	unsigned char nearby_teammates[8][16];
	int nearby_teammates_num = 0, l;
	edict_t *ent = NULL;

	nearby_teammates_num = 0;

	while ((ent = findradius(ent, self->s.origin, 1500)) != NULL) {
		if (ent == self || !ent->client || !CanDamage(ent, self) || !OnSameTeam(ent, self))
			continue;

		Q_strncpyz(nearby_teammates[nearby_teammates_num], ent->client->pers.netname, sizeof(nearby_teammates[0]));

		nearby_teammates_num++;
		if (nearby_teammates_num >= 8)
			break;
	}

	if (nearby_teammates_num == 0) {
		strcpy(buf, "nobody");
		return;
	}

	strcpy(buf, nearby_teammates[0]);
	for (l = 1; l < nearby_teammates_num; l++)
	{
		if (l == nearby_teammates_num - 1)
			Q_strncatz(buf, " and ", PARSE_BUFSIZE);
		else
			Q_strncatz(buf, ", ", PARSE_BUFSIZE);

		Q_strncatz(buf, nearby_teammates[l], PARSE_BUFSIZE);
	}
}
