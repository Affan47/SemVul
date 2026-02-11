find_submodel_instance_point(vec3d *outpnt, object *ship_obj, int submodel_num)
{
	Assert(ship_obj->type == OBJ_SHIP);

	vm_vec_zero(outpnt);
	matrix submodel_instance_matrix, rotation_matrix, inv_orientation;

	polymodel_instance *pmi = model_get_instance(Ships[ship_obj->instance].model_instance_num);
	polymodel *pm = model_get(Ship_info[Ships[ship_obj->instance].ship_info_index].model_num);

	int mn = submodel_num;
	while ( (mn >= 0) && (pm->submodel[mn].parent >= 0) ) {
		vec3d offset = pm->submodel[mn].offset;

		int parent_mn = pm->submodel[mn].parent;

		if (pm->submodel[parent_mn].can_move) {
			rotation_matrix = pm->submodel[parent_mn].orientation;
			vm_rotate_matrix_by_angles(&rotation_matrix, &pmi->submodel[parent_mn].angs);

			vm_copy_transpose_matrix(&inv_orientation, &pm->submodel[parent_mn].orientation);

			vm_matrix_x_matrix(&submodel_instance_matrix, &rotation_matrix, &inv_orientation);

			vec3d tvec = offset;
			vm_vec_unrotate(&offset, &tvec, &submodel_instance_matrix);
		}

		vm_vec_add2(outpnt, &offset);

		mn = parent_mn;
	}
}
