update_mm_labels(tb_crop_t * tb_crop, AmitkView view) {
  AmitkPoint temp_rp;
  range_t i_range;
  AmitkDim i_dim;
  gchar * temp_string;

  for (i_range=0; i_range<NUM_RANGES; i_range++) {
    VOXEL_TO_POINT(tb_crop->range[i_range], AMITK_DATA_SET_VOXEL_SIZE(tb_crop->data_set), temp_rp);
    temp_rp = amitk_space_s2b(AMITK_SPACE(tb_crop->data_set), temp_rp);
    for (i_dim=0; i_dim<=AMITK_DIM_Z; i_dim++) {
      if (voxel_get_dim(AMITK_DATA_SET_DIM(tb_crop->data_set), i_dim) > 1) {
	temp_string = g_strdup_printf("%g", point_get_component(temp_rp, i_dim));
	gtk_label_set_text(GTK_LABEL(tb_crop->mm_label[view][i_dim][i_range]), temp_string);
	g_free(temp_string);
      }
    }
  }
  return;
}
