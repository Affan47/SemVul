p_pw_set_mask_name_dependent_widget_sensitivity(GapStbPropWidget *pw, gint active_index)
{
  gboolean l_sensitive;
  gboolean l_show;

  l_sensitive = TRUE;
  if(active_index <= 0)
  {

    l_sensitive = FALSE;
  }
  l_show = l_sensitive;

  p_pw_nullable_widget_set_sensitive(pw->mask_anchor_label, l_sensitive, l_show);
  p_pw_nullable_widget_set_sensitive(pw->pw_mask_enable_toggle, l_sensitive, l_show);
  p_pw_nullable_widget_set_sensitive(pw->pw_mask_anchor_radio_button_arr[0], l_sensitive, l_show);
  p_pw_nullable_widget_set_sensitive(pw->pw_mask_anchor_radio_button_arr[1], l_sensitive, l_show);

  p_pw_nullable_gimp_scale_entry_set_sensitive(pw->pw_spinbutton_mask_stepsize_adj
      , l_sensitive
      , l_show
      );

}
