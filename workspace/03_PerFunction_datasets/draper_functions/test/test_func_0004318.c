vm_vec_delta_ang(vec3d *v0,vec3d *v1,vec3d *fvec)
{
	float t;
	vec3d t0,t1,t2;

	vm_vec_copy_normalize(&t0,v0);
	vm_vec_copy_normalize(&t1,v1);

	if (NULL == fvec) {
		t = vm_vec_delta_ang_norm(&t0, &t1, NULL);
	} else {
		vm_vec_copy_normalize(&t2,fvec);
		t = vm_vec_delta_ang_norm(&t0,&t1,&t2);
	}

	return t;
}
