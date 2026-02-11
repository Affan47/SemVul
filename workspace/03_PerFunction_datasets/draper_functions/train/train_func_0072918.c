ai_endangered_time(object *ship_objp, object *weapon_objp)
{
	float		to_dot, from_dot, dist;

	dist = compute_dots(ship_objp, weapon_objp, &to_dot, &from_dot);


	if (weapon_objp->phys_info.speed < 1.0f)
		return dist + 1.0f;
	else if ((from_dot > 0.1f) && (dist/(from_dot*from_dot) < 48*ship_objp->radius))
		return dist / weapon_objp->phys_info.speed;
	else
		return -1.0f;
}
