CL_GetEntitySoundOrigin (int ent, vec3_t org)
{
	centity_t	*cent;

	if ((unsigned)ent >= MAX_EDICTS)
		Com_Error(ERR_DROP, "CL_GetEntityOrigin: ent = %i", ent);


	if (ent == cl.playernum + 1)
	{
		VectorCopy (cl.refdef.vieworg, org);
		return;
	}

	cent = &cl_entities[ent];


	if (cent->current.renderfx & (RF_FRAMELERP|RF_BEAM))
	{

		org[0] = cent->current.old_origin[0] + (cent->current.origin[0] - cent->current.old_origin[0]) * cl.lerpfrac;
		org[1] = cent->current.old_origin[1] + (cent->current.origin[1] - cent->current.old_origin[1]) * cl.lerpfrac;
		org[2] = cent->current.old_origin[2] + (cent->current.origin[2] - cent->current.old_origin[2]) * cl.lerpfrac;
	}
	else
	{

		org[0] = cent->prev.origin[0] + (cent->current.origin[0] - cent->prev.origin[0]) * cl.lerpfrac;
		org[1] = cent->prev.origin[1] + (cent->current.origin[1] - cent->prev.origin[1]) * cl.lerpfrac;
		org[2] = cent->prev.origin[2] + (cent->current.origin[2] - cent->prev.origin[2]) * cl.lerpfrac;
	}


	if (cent->current.solid == 31)
	{
		vec3_t		midPoint;
		cmodel_t	*cmodel = cl.model_clip[cent->current.modelindex];

		if (!cmodel)
			return;

		VectorAvg(cmodel->mins, cmodel->maxs, midPoint);
		VectorAdd(org, midPoint, org);
	}
}
