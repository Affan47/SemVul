objects_will_collide(object *A, object *B, float duration, float radius_scale)
{
	object	A_future;
	vec3d	hitpos;


	A_future = *A;
	vm_vec_scale_add2(&A_future.pos, &A->phys_info.vel, duration);

	if (radius_scale == 0.0f) {
		return ship_check_collision_fast(B, &A_future, &hitpos );
	} else {
		float		size_A, size_B, dist, r;
		vec3d	nearest_point;

		size_A = A->radius * radius_scale;
		size_B = B->radius * radius_scale;


		if (A->phys_info.speed != 0.0f) {
			r = find_nearest_point_on_line(&nearest_point, &A->pos, &A_future.pos, &B->pos);
			if (r < 0) {
				nearest_point = A->pos;
			} else if (r > 1) {
				nearest_point = A_future.pos;
			}
			dist = vm_vec_dist_quick(&B->pos, &nearest_point);
			return (dist < size_A + size_B);
		} else {
			return vm_vec_dist_quick(&B->pos, &A->pos) < size_A + size_B;
		}
	}
}
