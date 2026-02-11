stars_get_sun_pos(int sun_n, vec3d *pos)
{
	vec3d temp;
	matrix rot;


	Assert( sun_n < (int)Suns.size() );

	if ( (sun_n >= (int)Suns.size()) || (sun_n < 0) ) {
		return;
	}


	temp = vmd_zero_vector;
	temp.xyz.z = 1.0f;


	vm_angles_2_matrix(&rot, &Suns[sun_n].ang);
	vm_vec_rotate(pos, &temp, &rot);
}
