SV_ClipMoveToEntities ( moveclip_t *clip )
{
	int			i, num;
	edict_t		*touchlist[MAX_EDICTS], *touch;
	trace_t		trace;
	int			headnode;
	float		*angles;

	num = SV_AreaEdicts (clip->boxmins, clip->boxmaxs, touchlist
		, MAX_EDICTS, AREA_SOLID);


	for (i=0 ; i<num ; i++)
	{
		touch = touchlist[i];
		if (touch->solid == SOLID_NOT)
			continue;
		if (touch == clip->passedict)
			continue;
		if (clip->trace.allsolid)
			return;
		if (clip->passedict)
		{
		 	if (touch->owner == clip->passedict)
				continue;
			if (clip->passedict->owner == touch)
				continue;
		}

		if ( !(clip->contentmask & CONTENTS_DEADMONSTER)
		&& (touch->svflags & SVF_DEADMONSTER) )
				continue;


		headnode = SV_HullForEntity (touch);
		angles = touch->s.angles;
		if (touch->solid != SOLID_BSP)
			angles = vec3_origin;

		if (touch->svflags & SVF_MONSTER)
			trace = CM_TransformedBoxTrace (clip->start, clip->end,
				clip->mins2, clip->maxs2, headnode, clip->contentmask,
				touch->s.origin, angles);
		else
			trace = CM_TransformedBoxTrace (clip->start, clip->end,
				clip->mins, clip->maxs, headnode,  clip->contentmask,
				touch->s.origin, angles);

		if (trace.allsolid || trace.startsolid ||
		trace.fraction < clip->trace.fraction)
		{
			trace.ent = touch;
		 	if (clip->trace.startsolid)
			{
				clip->trace = trace;
				clip->trace.startsolid = true;
			}
			else
				clip->trace = trace;
		}
		else if (trace.startsolid)
			clip->trace.startsolid = true;
	}
}
