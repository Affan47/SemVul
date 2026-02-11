fds_aux(float *dot, float *tts, vec3d *pos, float dtime, object *objp)
{
	vec3d	v2s;

	vm_vec_sub(&v2s, pos, &objp->pos);
	*dot = vm_vec_dot(&v2s, &objp->orient.vec.fvec);

	if (*dot > 0.0f) {
		float	dist;

		dist = vm_vec_dist(&objp->pos, pos);

		if (dist > 0.1f)
			*dot /= dist;
		else
			*dot = 1.0f;

		if (objp->phys_info.speed > 0.1f)
			*tts = dist / objp->phys_info.speed;
		else
			*tts = dist * 100.0f;
	}
}
