dialog_set_sensitive(ui_render_movie_t * ui_render_movie, gboolean sensitive) {

  AmitkAxis i_axis;

  gtk_widget_set_sensitive(ui_render_movie->duration_spin_button, sensitive);
  for (i_axis=0; i_axis<AMITK_AXIS_NUM; i_axis++)
    gtk_widget_set_sensitive(ui_render_movie->axis_spin_button[i_axis], sensitive);
  gtk_widget_set_sensitive(ui_render_movie->start_time_spin_button, sensitive);
  gtk_widget_set_sensitive(ui_render_movie->end_time_spin_button, sensitive);
  gtk_widget_set_sensitive(ui_render_movie->start_frame_spin_button, sensitive);
  gtk_widget_set_sensitive(ui_render_movie->end_frame_spin_button, sensitive);
  gtk_widget_set_sensitive(ui_render_movie->dynamic_type, sensitive);
  gtk_dialog_set_response_sensitive(GTK_DIALOG(ui_render_movie->dialog),
				    AMITK_RESPONSE_EXECUTE, sensitive);
}
