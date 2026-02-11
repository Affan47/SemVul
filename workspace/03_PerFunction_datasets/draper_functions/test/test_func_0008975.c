ai_return_path_num_from_dockbay(object *dockee_objp, int dockbay_index)
{
	if ( dockbay_index < 0 || dockee_objp == NULL ) {
		Int3();
		return -1;
	}

	if ( dockee_objp->type == OBJ_SHIP ) {
		int			path_num;
		polymodel	*pm;

		pm = model_get(Ship_info[Ships[dockee_objp->instance].ship_info_index].model_num );

		Assert(pm->n_docks > dockbay_index);
		Assert(pm->docking_bays[dockbay_index].num_spline_paths > 0);
		Assert(pm->docking_bays[dockbay_index].splines != NULL);

		if(pm->n_docks <= dockbay_index){
			return -1;
		}
		if(pm->docking_bays[dockbay_index].num_spline_paths <= 0){
			return -1;
		}
		if(pm->docking_bays[dockbay_index].splines == NULL){
			return -1;
		}


		path_num = pm->docking_bays[dockbay_index].splines[0];
		return path_num;
	} else {
		return -1;
	}
}
