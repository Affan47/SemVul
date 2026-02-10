vm_vec_dist_to_line(vec3d *p, vec3d *l0, vec3d *l1, vec3d *nearest, float *dist)
{
	vec3d a, b, c;
	float b_mag, comp;

#ifndef NDEBUG
	if(vm_vec_same(l0, l1)){
		*nearest = vmd_zero_vector;
		return -1;
	}
#endif


	vm_vec_sub(&a, p, l0);
	vm_vec_sub(&b, l1, l0);
	b_mag = vm_vec_copy_normalize(&c, &b);


	comp = vm_vec_dotprod(&a, &b) / b_mag;


	vm_vec_scale_add(nearest, l0, &c, comp);


	if(dist != NULL){
		*dist = vm_vec_dist(nearest, p);
	}


	if(comp < 0.0f){
		return -1;
	} else if(comp > b_mag){
		return 1;
	}
	return 0;
}
