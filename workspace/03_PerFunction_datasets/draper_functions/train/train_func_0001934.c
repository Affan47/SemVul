canvas_update_scrollbar(AmitkCanvas * canvas, AmitkPoint center, amide_real_t thickness) {

  AmitkCorners view_corner;
  amide_real_t upper, lower;
  amide_real_t min_voxel_size;
  AmitkPoint zp_start;
  GList * volumes;
  GList * data_sets;


  if (canvas->study == NULL) return;


  view_corner[0]=zero_point;
  view_corner[1]=zero_point;

  volumes = amitk_object_get_selected_children_of_type(AMITK_OBJECT(canvas->study),
						       AMITK_OBJECT_TYPE_VOLUME,
						       canvas->view_mode,
						       TRUE);
  amitk_volumes_get_enclosing_corners(volumes, AMITK_SPACE(canvas->volume), view_corner);
  amitk_objects_unref(volumes);

  data_sets = amitk_object_get_selected_children_of_type(AMITK_OBJECT(canvas->study),
							 AMITK_OBJECT_TYPE_DATA_SET,
							 canvas->view_mode,
							 TRUE);
  min_voxel_size = amitk_data_sets_get_min_voxel_size(data_sets);
  amitk_objects_unref(data_sets);

  upper = view_corner[1].z;
  lower = view_corner[0].z;


  zp_start = amitk_space_b2s(AMITK_SPACE(canvas->volume), center);


  if (zp_start.z < lower) {

    if (zp_start.z < lower-thickness)
      zp_start.z = (upper-lower)/2.0+lower;
    else
      zp_start.z = lower;

  } else if (zp_start.z > upper) {

    if (zp_start.z > lower+thickness)
      zp_start.z = (upper-lower)/2.0+lower;
    else
      zp_start.z = upper;
  }


  GTK_ADJUSTMENT(canvas->scrollbar_adjustment)->upper = upper;
  GTK_ADJUSTMENT(canvas->scrollbar_adjustment)->lower = lower;
  GTK_ADJUSTMENT(canvas->scrollbar_adjustment)->step_increment = min_voxel_size;
  GTK_ADJUSTMENT(canvas->scrollbar_adjustment)->page_increment = (thickness/2.0 < min_voxel_size) ? min_voxel_size : thickness/2.0;
  GTK_ADJUSTMENT(canvas->scrollbar_adjustment)->page_size = 0;
  GTK_ADJUSTMENT(canvas->scrollbar_adjustment)->value = zp_start.z;


  g_signal_handlers_block_by_func(G_OBJECT(canvas->scrollbar_adjustment),
				   G_CALLBACK(canvas_scrollbar_adjustment_cb), canvas);
  gtk_adjustment_changed(GTK_ADJUSTMENT(canvas->scrollbar_adjustment));
  g_signal_handlers_unblock_by_func(G_OBJECT(canvas->scrollbar_adjustment),
				     G_CALLBACK(canvas_scrollbar_adjustment_cb), canvas);

  return;
}
