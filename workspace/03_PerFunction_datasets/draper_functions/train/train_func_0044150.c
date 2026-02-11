fvi_two_lines_in_3space(vec3d *p1, vec3d *v1, vec3d *p2, vec3d *v2, float *s, float *t)
{
	vec3d cross,delta;
	vm_vec_crossprod(&cross, v1, v2);
	vm_vec_sub(&delta, p2, p1);

	float denominator = vm_vec_mag_squared(&cross);
	float num_t, num_s;

	if (denominator > 1e-10) {
		num_s = matrix_determinant_from_vectors(&delta, v2, &cross);
		*s = num_s / denominator;

		num_t = matrix_determinant_from_vectors(&delta, v1, &cross);
		*t = num_t / denominator;
	} else {

		*s = FLT_MAX;
		*t = FLT_MAX;
	}
}
