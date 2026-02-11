gf_quat_from_rotation(GF_Vec4 rot)
{
	GF_Vec4 res;
	Fixed s;
	Fixed scale = gf_sqrt( gf_mulfix(rot.x, rot.x) + gf_mulfix(rot.y, rot.y) + gf_mulfix(rot.z, rot.z));


	if (scale == 0) {
		res.q = FIX_ONE;
		res.x = 0;
		res.y = 0;
		res.z = 0;
	} else {
		s = gf_sin(rot.q/2);
		res.q = gf_cos(rot.q / 2);
		res.x = gf_muldiv(s, rot.x, scale);
		res.y = gf_muldiv(s, rot.y, scale);
		res.z = gf_muldiv(s, rot.z, scale);
		gf_quat_norm(res);
	}
	return res;
}
