will_collide_with_big_ship(object *objp, vec3d *goal_point, object *big_objp, vec3d *collision_point, float delta_time)
{
	float		radius;
	vec3d	end_pos;

	radius = big_objp->radius + delta_time * objp->phys_info.speed;

	if (vm_vec_dist_quick(&big_objp->pos, &objp->pos) > radius) {
		return 0;
	}

	if (goal_point == NULL) {
		vm_vec_scale_add(&end_pos, &objp->pos, &objp->phys_info.vel, delta_time);
	} else {
		end_pos = *goal_point;
	}

	return will_collide_pp(&objp->pos, &end_pos, objp->radius, big_objp, collision_point);
}
