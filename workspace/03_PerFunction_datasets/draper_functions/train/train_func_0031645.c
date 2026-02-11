ai_need_new_target(object *pl_objp, int target_objnum)
{
	object *objp;

	if ( target_objnum < 0 ) {
		return 1;
	}

	objp = &Objects[target_objnum];

	if ( (objp->type != OBJ_SHIP) && (objp->type != OBJ_ASTEROID) && (objp->type != OBJ_WEAPON) ) {
		return 1;
	}

	if ( objp->type == OBJ_SHIP ) {
		if ( Ships[objp->instance].flags & SF_DYING ) {
			return 1;
		} else if (Ships[objp->instance].team == Ships[pl_objp->instance].team)
			return 1;
	}

	return 0;
}
