KillBox (edict_t * ent)
{
	trace_t tr;

	while (1)
	{
		tr = gi.trace (ent->s.origin, ent->mins, ent->maxs, ent->s.origin, NULL, MASK_PLAYERSOLID);
		if (!tr.ent)
			break;


		T_Damage (tr.ent, ent, ent, vec3_origin, ent->s.origin, vec3_origin,
			100000, 0, DAMAGE_NO_PROTECTION, MOD_TELEFRAG);


		if (tr.ent->solid)
			return false;
	}

	return true;
}
