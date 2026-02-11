reset()
{
	flags = CAM_DEFAULT_FLAGS;

	object_host = object_target = object_h();
	object_host_submodel = object_target_submodel = -1;

	c_fov = VIEWER_ZOOM_DEFAULT;
	c_pos = vmd_zero_vector;
	c_ori = vmd_identity_matrix;

	func_custom_position = NULL;
	func_custom_orientation = NULL;

	fov.clear();
	fov.set(VIEWER_ZOOM_DEFAULT);

	pos_x.clear();
	pos_y.clear();
	pos_z.clear();

	for(int i = 0; i < 9; i++)
	{
		ori[i].clear();
		ori[i].set(vmd_identity_matrix.a1d[i]);
	}
}
