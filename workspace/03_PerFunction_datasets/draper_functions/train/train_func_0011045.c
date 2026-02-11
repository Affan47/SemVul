camera_get_orientation(SFVec3f pos, SFVec3f target, SFVec3f up)
{
	SFVec3f dir, tmp, v, axis, new_y;
	SFVec4f norm, inv_norm, y_quat, ny_quat, rot_y, rot;

	gf_vec_diff(dir, target, pos);
	gf_vec_norm(&dir);
	tmp = gf_vec_scale(dir, gf_vec_dot(up, dir));
	gf_vec_diff(v, up, tmp);
	gf_vec_norm(&v);
	axis.x = dir.y; axis.y = -dir.x; axis.z = 0;

	if (gf_vec_dot(axis, axis) < FIX_EPSILON) {
		if (dir.z> 0) {
			norm.x = 0; norm.y = FIX_ONE; norm.z = 0; norm.q = 0;
		} else {
			norm.x = 0; norm.y = 0; norm.z = 0; norm.q = FIX_ONE;
		}
	} else {
		gf_vec_norm(&axis);
		norm = gf_quat_from_axis_cos(axis, -dir.z);
	}

    inv_norm.x = -norm.x; inv_norm.y = -norm.y; inv_norm.z = -norm.z; inv_norm.q = norm.q;

	y_quat.x = y_quat.z = y_quat.q = 0; y_quat.y = FIX_ONE;
	ny_quat = gf_quat_multiply(&norm, &y_quat);
	ny_quat = gf_quat_multiply(&ny_quat, &inv_norm);

	new_y.x = ny_quat.x; new_y.y = ny_quat.y; new_y.z = ny_quat.z;

	tmp = gf_vec_cross(new_y, v);

	if (gf_vec_dot(tmp, tmp) < FIX_EPSILON) {


		tmp.x = 0; tmp.y = -v.z; tmp.z = v.y;
		if (gf_vec_dot(tmp, tmp) < FIX_EPSILON) {
			tmp.x = v.z; tmp.y = 0; tmp.z = -v.x;
		}
	}
	gf_vec_norm(&tmp);

	rot_y = gf_quat_from_axis_cos(tmp, gf_vec_dot(new_y, v));


	rot = gf_quat_multiply(&rot_y, &norm);
	return gf_quat_to_rotation(&rot);
}
