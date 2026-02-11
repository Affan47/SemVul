DetermineViewedEnemy (edict_t * ent)
{
	vec3_t forward, dir;
	trace_t tr;
	edict_t *who, *best;
	float bd = 0, d;
	int i;

	AngleVectors (ent->client->v_angle, forward, NULL, NULL);
	VectorScale (forward, 8192, forward);
	VectorAdd (ent->s.origin, forward, forward);
	PRETRACE ();
	tr = gi.trace (ent->s.origin, NULL, NULL, forward, ent, MASK_SOLID);
	POSTTRACE ();
	if (tr.fraction < 1 && tr.ent && tr.ent->client)
	{
		return NULL;
	}

	AngleVectors (ent->client->v_angle, forward, NULL, NULL);
	best = NULL;
	for (i = 1; i <= maxclients->value; i++)
	{
		who = g_edicts + i;
		if (!who->inuse)
			continue;
		VectorSubtract (who->s.origin, ent->s.origin, dir);
		VectorNormalize (dir);
		d = DotProduct (forward, dir);
		if (d > bd && loc_CanSee (ent, who) && who->solid != SOLID_NOT &&
			who->deadflag != DEAD_DEAD && !OnSameTeam (who, ent))
		{
			bd = d;
			best = who;
		}
	}

	if (bd > 0.90)
		return best;

	return NULL;
}
