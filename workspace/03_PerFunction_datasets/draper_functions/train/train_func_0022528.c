vm_check_matrix_for_zeros(matrix *m)
{
	if (!m->vec.fvec.xyz.x && !m->vec.fvec.xyz.y && !m->vec.fvec.xyz.z)
		return 1;
	if (!m->vec.rvec.xyz.x && !m->vec.rvec.xyz.y && !m->vec.rvec.xyz.z)
		return 1;
	if (!m->vec.uvec.xyz.x && !m->vec.uvec.xyz.y && !m->vec.uvec.xyz.z)
		return 1;

	if (!m->vec.fvec.xyz.x && !m->vec.rvec.xyz.x && !m->vec.uvec.xyz.x)
		return 1;
	if (!m->vec.fvec.xyz.y && !m->vec.rvec.xyz.y && !m->vec.uvec.xyz.y)
		return 1;
	if (!m->vec.fvec.xyz.z && !m->vec.rvec.xyz.z && !m->vec.uvec.xyz.z)
		return 1;

	return 0;
}
