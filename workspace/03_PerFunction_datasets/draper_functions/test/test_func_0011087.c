maybe_dock_obstructed(object *cur_objp, object *goal_objp, int big_only_flag)
{
	vec3d	*goalpos, *curpos;
	float		radius;
	ai_info	*aip;
	int		collide_objnum;

	aip = &Ai_info[Ships[cur_objp->instance].ai_index];

	Ai_info[Ships[goal_objp->instance].ai_index].ai_flags &= ~AIF_REPAIR_OBSTRUCTED;

	if (goal_objp != Player_obj)
		return -1;

	curpos = &cur_objp->pos;
	radius = cur_objp->radius;
	goalpos = &Path_points[aip->path_cur].pos;
	collide_objnum = pp_collide_any(curpos, goalpos, radius, cur_objp, goal_objp, big_only_flag);

	if (collide_objnum != -1)
		Ai_info[Ships[goal_objp->instance].ai_index].ai_flags |= AIF_REPAIR_OBSTRUCTED;

	return collide_objnum;
}
