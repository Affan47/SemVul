model_collide_preprocess_subobj(vec3d *pos, matrix *orient, polymodel *pm,  polymodel_instance *pmi, int subobj_num)
{
	submodel_instance *smi = &pmi->submodel[subobj_num];

	smi->mc_base = *pos;
	smi->mc_orient = *orient;

	int i = pm->submodel[subobj_num].first_child;

	while ( i >= 0 ) {
		angles angs = pmi->submodel[i].angs;
		bsp_info * csm = &pm->submodel[i];

		matrix tm = IDENTITY_MATRIX;

		vm_vec_unrotate(pos, &csm->offset, &smi->mc_orient );
		vm_vec_add2(pos, &smi->mc_base);

		if( vm_matrix_same(&tm, &csm->orientation)) {

			vm_angles_2_matrix(&tm, &angs);
		} else {
			matrix rotation_matrix = csm->orientation;
			vm_rotate_matrix_by_angles(&rotation_matrix, &angs);

			matrix inv_orientation;
			vm_copy_transpose_matrix(&inv_orientation, &csm->orientation);

			vm_matrix_x_matrix(&tm, &rotation_matrix, &inv_orientation);
		}

		vm_matrix_x_matrix(orient, &smi->mc_orient, &tm);

		model_collide_preprocess_subobj(pos, orient, pm, pmi, i);

		i = csm->next_sibling;
	}
}
