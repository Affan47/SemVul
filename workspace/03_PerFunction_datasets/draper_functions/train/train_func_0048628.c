ai_set_evade_object(object *objp, object *other_objp)
{
	ship		*shipp;
	ai_info	*aip;
	int		other_objnum;

	Assert(objp->type == OBJ_SHIP);
	Assert(objp->instance >= 0);

	shipp = &Ships[objp->instance];

	Assert(shipp->ai_index >= 0);

	aip = &Ai_info[shipp->ai_index];

	other_objnum = OBJ_INDEX(other_objp);
	Assert(other_objnum >= 0);

	Assert(other_objnum != Ships[aip->shipnum].objnum);
	aip->target_objnum = other_objnum;

	aip->mode = AIM_EVADE;
}
