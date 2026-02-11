ui_study_update_thickness(ui_study_t * ui_study, amide_real_t thickness) {

  amide_real_t min_voxel_size, max_size;


  if (ui_study->thickness_spin == NULL) return;

  min_voxel_size = amitk_data_sets_get_min_voxel_size(AMITK_OBJECT_CHILDREN(ui_study->study));
  max_size = amitk_volumes_get_max_size(AMITK_OBJECT_CHILDREN(ui_study->study));

  if ((min_voxel_size < 0)  || (max_size < 0)) return;


  g_signal_handlers_block_by_func(G_OBJECT(ui_study->thickness_spin),
				  G_CALLBACK(ui_study_cb_thickness), ui_study);


  if (thickness < min_voxel_size)
    thickness = min_voxel_size;

  gtk_spin_button_set_value(GTK_SPIN_BUTTON(ui_study->thickness_spin), thickness);
  gtk_spin_button_set_increments(GTK_SPIN_BUTTON(ui_study->thickness_spin), min_voxel_size, min_voxel_size);
  gtk_spin_button_set_range(GTK_SPIN_BUTTON(ui_study->thickness_spin), min_voxel_size, max_size);
  gtk_spin_button_configure(GTK_SPIN_BUTTON(ui_study->thickness_spin),NULL, thickness,
			    gtk_spin_button_get_digits(GTK_SPIN_BUTTON(ui_study->thickness_spin)));

  g_signal_handlers_unblock_by_func(G_OBJECT(ui_study->thickness_spin),
				    G_CALLBACK(ui_study_cb_thickness), ui_study);

  return;
}
