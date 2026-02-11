world_find_real_model_point(vec3d *out, vec3d *world_pt, polymodel *pm, int submodel_num, matrix *orient, vec3d *pos)
{
	vec3d tempv1, tempv2;


	vm_vec_sub(&tempv1, world_pt, pos);
	vm_vec_rotate(&tempv2, &tempv1, orient);

	if (pm->submodel[submodel_num].parent == -1) {
		*out  = tempv2;
		return;
	}


	make_submodel_world_matrix(pm,submodel_num, &tempv2);
	*out = tempv2;
}
