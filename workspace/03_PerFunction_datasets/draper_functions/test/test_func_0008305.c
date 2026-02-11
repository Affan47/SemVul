model_get_rotating_submodel_list(SCP_vector<int> *submodel_vector, object *objp)
{
	Assert(objp->type == OBJ_SHIP);


	int modelnum = Ship_info[Ships[objp->instance].ship_info_index].model_num;
	polymodel *pm = model_get(modelnum);
	bsp_info *child_submodel;

	child_submodel = &pm->submodel[pm->detail[0]];

	if(child_submodel->no_collisions) {
		return;
	}

	int i = child_submodel->first_child;
	while ( i >= 0 )	{
		child_submodel = &pm->submodel[i];


		if ( !child_submodel->blown_off && (child_submodel->i_replace == -1) && !child_submodel->no_collisions && !child_submodel->nocollide_this_only)	{


			if (child_submodel->movement_type == MOVEMENT_TYPE_ROT) {


				ship *pship = &Ships[objp->instance];
				ship_subsys *subsys;

				for ( subsys = GET_FIRST(&pship->subsys_list); subsys !=END_OF_LIST(&pship->subsys_list); subsys = GET_NEXT(subsys) ) {
					Assert(subsys->system_info->model_num == modelnum);
					if (i == subsys->system_info->subobj_num) {

						float delta_angle = get_submodel_delta_angle(&subsys->submodel_info_1);
						if (delta_angle < MAX_SUBMODEL_COLLISION_ROT_ANGLE) {
							submodel_vector->push_back(i);
						}
						break;
					}
				}
			}
		}
		i = child_submodel->next_sibling;
	}


#ifdef MODEL_CHECK
	ship *pship = &Ships[objp->instance];
	for (size_t idx=0; idx<submodel_vector->size(); idx++) {
		int valid = rotating_submodel_has_ship_subsys(submodel_vector[idx], pship);

		if ( !valid ) {

			Warning( LOCATION, "Ship %s has rotating submodel [%s] without ship subsystem\n", pship->ship_name, pm->submodel[submodel_vector[idx]].name );
			pm->submodel[submodel_vector[idx]].movement_type &= ~MOVEMENT_TYPE_ROT;
			submodel_vector->erase(submodel_vector->begin()+i);
		}
	}
#endif

}
