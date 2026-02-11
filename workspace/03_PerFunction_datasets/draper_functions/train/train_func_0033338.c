vm_vector_2_matrix_gen_vectors(matrix *m)
{
	vec3d *xvec=&m->vec.rvec;
	vec3d *yvec=&m->vec.uvec;
	vec3d *zvec=&m->vec.fvec;

	if ((zvec->xyz.x==0.0f) && (zvec->xyz.z==0.0f)) {
		m->vec.rvec.xyz.x = 1.0f;
		m->vec.uvec.xyz.z = (zvec->xyz.y<0.0f)?1.0f:-1.0f;

		m->vec.rvec.xyz.y = m->vec.rvec.xyz.z = m->vec.uvec.xyz.x = m->vec.uvec.xyz.y = 0.0f;
	}
	else {

		xvec->xyz.x = zvec->xyz.z;
		xvec->xyz.y = 0.0f;
		xvec->xyz.z = -zvec->xyz.x;

		vm_vec_normalize(xvec);

		vm_vec_crossprod(yvec,zvec,xvec);

	}
}
