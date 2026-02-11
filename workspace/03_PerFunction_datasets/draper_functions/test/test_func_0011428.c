CL_PMTrace (vec3_t start, vec3_t mins, vec3_t maxs, vec3_t end)
{
	trace_t	t;


	t = CM_BoxTrace (start, end, mins, maxs, 0, MASK_PLAYERSOLID);
	if (t.fraction < 1.0)
		t.ent = (struct edict_s *)1;


	CL_ClipMoveToEntities (start, mins, maxs, end, &t);

	return t;
}
