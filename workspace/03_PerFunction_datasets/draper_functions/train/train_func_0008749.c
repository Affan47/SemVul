fvi_closest_point_on_line_segment(vec3d *closest_point, vec3d *fixed_point, vec3d *line_point1, vec3d *line_point2)
{
	vec3d delta_x, line_velocity;
	float t;

	vm_vec_sub(&line_velocity, line_point2, line_point1);
	vm_vec_sub(&delta_x, line_point1, fixed_point);
	t = -vm_vec_dotprod(&delta_x, &line_velocity) / vm_vec_mag_squared(&line_velocity);


	if (t < 0) {
		t = 0.0f;
	} else if (t > 1) {
		t = 1.0f;
	}

	vm_vec_scale_add(closest_point, line_point1, &line_velocity, t);
}
