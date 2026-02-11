pp_collide_any(vec3d *curpos, vec3d *goalpos, float radius, object *ignore_objp1, object *ignore_objp2, int big_only_flag)
{
	ship_obj	*so;

	for ( so = GET_FIRST(&Ship_obj_list); so != END_OF_LIST(&Ship_obj_list); so = GET_NEXT(so) ) {
		object *objp = &Objects[so->objnum];

		if (big_only_flag) {
			if (!(Ship_info[Ships[objp->instance].ship_info_index].flags & (SIF_BIG_SHIP | SIF_HUGE_SHIP)))
				continue;
		}

		if ((objp != ignore_objp1) && (objp != ignore_objp2)) {
			if (pp_collide(curpos, goalpos, objp, radius))
				return OBJ_INDEX(objp);
		}
	}

	return -1;
}
