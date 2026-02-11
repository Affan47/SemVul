threshold_update_color_table(AmitkThreshold * threshold, AmitkViewMode view_mode) {

  g_return_if_fail(AMITK_IS_DATA_SET(threshold->data_set));


  g_signal_handlers_block_by_func(G_OBJECT(threshold->color_table_menu[view_mode]), G_CALLBACK(color_table_cb), threshold);
  gtk_combo_box_set_active(GTK_COMBO_BOX(threshold->color_table_menu[view_mode]),
			   AMITK_DATA_SET_COLOR_TABLE(threshold->data_set, view_mode));
  g_signal_handlers_unblock_by_func(G_OBJECT(threshold->color_table_menu[view_mode]), G_CALLBACK(color_table_cb), threshold);

  if (view_mode == AMITK_VIEW_MODE_SINGLE) {
  } else {
    g_signal_handlers_block_by_func(G_OBJECT(threshold->color_table_independent[view_mode]), G_CALLBACK(color_table_independent_cb), threshold);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(threshold->color_table_independent[view_mode]),
				 AMITK_DATA_SET_COLOR_TABLE_INDEPENDENT(threshold->data_set, view_mode));
    g_signal_handlers_unblock_by_func(G_OBJECT(threshold->color_table_independent[view_mode]), G_CALLBACK(color_table_independent_cb), threshold);

    gtk_widget_set_sensitive(threshold->color_table_menu[view_mode],
			     AMITK_DATA_SET_COLOR_TABLE_INDEPENDENT(threshold->data_set, view_mode));
  }

  return;
}
