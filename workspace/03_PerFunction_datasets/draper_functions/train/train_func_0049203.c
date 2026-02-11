p_morph_response(GtkWidget *w, gint response_id, GapMorphGUIParams *mgup)
{
  GtkWidget *dialog;

  switch (response_id)
  {
    case GAP_MORPH_RESPONSE_RESET:
      gap_morph_exec_free_workpoint_list(&mgup->mgpp->master_wp_list);
      p_add_4corner_workpoints(mgup);
      p_set_upd_timer_request(mgup
                         ,GAP_MORPH_DLG_UPD_REQUEST_FULL_REFRESH
                         ,GAP_MORPH_DLG_UPD_REQUEST_FULL_REFRESH
                         );
      p_refresh_total_points_label(mgup);
      mgup->mgpp->tween_steps = 1;
      mgup->num_shapepoints = 16;
      mgup->mgpp->affect_radius = 100;
      mgup->mgpp->gravity_intensity = 2.0;
      mgup->mgpp->use_quality_wp_selection = FALSE;
      mgup->mgpp->use_gravity = FALSE;
      mgup->mgpp->create_tween_layers = TRUE;
      mgup->mgpp->have_workpointsets = FALSE;
      p_upd_widget_values(mgup);
      break;
    case GTK_RESPONSE_OK:
      if(mgup)
      {
        if (GTK_WIDGET_VISIBLE (mgup->shell))
        {
          gtk_widget_hide (mgup->shell);
        }
        mgup->run_flag = TRUE;
      }

    default:
      dialog = NULL;
      if(mgup)
      {
        dialog = mgup->shell;
        if(dialog)
        {
          mgup->shell = NULL;
          gtk_widget_destroy (dialog);
        }
      }
      gtk_main_quit ();
      break;
  }
}
