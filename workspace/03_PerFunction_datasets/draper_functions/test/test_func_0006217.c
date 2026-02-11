ai_chase_big_approach_set_goal(vec3d *goal_pos, object *attack_objp, object *target_objp, float *accel)
{
	float dist_to_goal;


	vm_vec_avg(goal_pos, &attack_objp->pos, &target_objp->pos);


	dist_to_goal = vm_vec_dist(goal_pos, &attack_objp->pos);


	if (dist_to_goal > 400.0f) {
		*accel = 1.0f;
	} else {
		*accel = dist_to_goal/400.0f;
	}
}
