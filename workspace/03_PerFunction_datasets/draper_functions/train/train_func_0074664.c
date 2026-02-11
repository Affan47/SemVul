camera_pos_past_target(vec3d *start, vec3d *current, vec3d *dest)
{
	vec3d num, den;
	float ratio;

	vm_vec_sub(&num, current, start);
	vm_vec_sub(&den, start, dest);

	ratio = vm_vec_mag_quick(&num) / vm_vec_mag_quick(&den);
	if (ratio >= 1.0f)
		return TRUE;

	return FALSE;
}
