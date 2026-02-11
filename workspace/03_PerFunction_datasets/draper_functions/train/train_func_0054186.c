p_upd_widget_values(GapMorphGUIParams *mgup)
{
  if(mgup)
  {
       gtk_adjustment_set_value(
            GTK_ADJUSTMENT(mgup->tween_steps_spinbutton_adj)
           ,mgup->mgpp->tween_steps);
       gtk_adjustment_set_value(
            GTK_ADJUSTMENT(mgup->num_shapepoints_adj)
           ,mgup->num_shapepoints);
       gtk_adjustment_set_value(
            GTK_ADJUSTMENT(mgup->affect_radius_spinbutton_adj)
           ,mgup->mgpp->affect_radius);
       gtk_adjustment_set_value(
            GTK_ADJUSTMENT(mgup->gravity_intensity_spinbutton_adj)
           ,mgup->mgpp->gravity_intensity);
       gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (mgup->use_quality_wp_selection_checkbutton)
                                    , mgup->mgpp->use_quality_wp_selection);
       gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (mgup->use_gravity_checkbutton)
                                    , mgup->mgpp->use_gravity);
       gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (mgup->create_tween_layers_checkbutton)
                                    , mgup->mgpp->create_tween_layers);
       gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (mgup->have_workpointsets_checkbutton)
                                    , mgup->mgpp->have_workpointsets);

  }
}
