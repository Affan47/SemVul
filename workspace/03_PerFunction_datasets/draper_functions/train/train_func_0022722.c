check_sphere_point( vec3d *point, vec3d *sphere_start, vec3d *sphere_vel, float radius, float *collide_time )
{
	vec3d delta_x;
	float delta_x_sqr, vs_sqr, delta_x_dot_vs;

	vm_vec_sub( &delta_x, sphere_start, point );
	delta_x_sqr = vm_vec_mag_squared( &delta_x );
	vs_sqr = vm_vec_mag_squared( sphere_vel );
	delta_x_dot_vs = vm_vec_dotprod( &delta_x, sphere_vel );

	float discriminant = delta_x_dot_vs*delta_x_dot_vs - vs_sqr*(delta_x_sqr - radius*radius);
	if (discriminant < 0) {
		return 0;
	}

	float radical, time1, time2;
	radical = fl_sqrt(discriminant);
	time1 = (-delta_x_dot_vs + radical) / vs_sqr;
	time2 = (-delta_x_dot_vs - radical) / vs_sqr;

	if (time1 > time2) {
		float temp = time1;
		time1 = time2;
		time2 = temp;
	}

	if (time1 >= 0 && time1 <= 1.0) {
		*collide_time = time1;
		return 1;
	}

	if (time2 >= 0 && time2 <= 1.0) {
		*collide_time = time2;
		return 1;
	}

	return 0;
}
