realign_outputs_after_resolution_change (CcDisplayPanel *self, GnomeRROutputInfo *output_that_changed, int old_width, int old_height)
{


  int i;
  int old_right_edge, old_bottom_edge;
  int dx, dy;
  int x, y, width, height;
  GnomeRROutputInfo **outputs;

  g_assert (self->priv->current_configuration != NULL);

  gnome_rr_output_info_get_geometry (output_that_changed, &x, &y, &width, &height);

  if (width == old_width && height == old_height)
    return;

  old_right_edge = x + old_width;
  old_bottom_edge = y + old_height;

  dx = width - old_width;
  dy = height - old_height;

  outputs = gnome_rr_config_get_outputs (self->priv->current_configuration);

  for (i = 0; outputs[i] != NULL; i++)
    {
      int output_x, output_y;
      int output_width, output_height;

      if (outputs[i] == output_that_changed || !gnome_rr_output_info_is_connected (outputs[i]))
        continue;

      gnome_rr_output_info_get_geometry (outputs[i], &output_x, &output_y, &output_width, &output_height);

      if (output_x >= old_right_edge)
         output_x += dx;
      else if (output_x + output_width == old_right_edge)
         output_x = x + width - output_width;

      if (output_y >= old_bottom_edge)
         output_y += dy;
      else if (output_y + output_height == old_bottom_edge)
         output_y = y + height - output_height;

      gnome_rr_output_info_set_geometry (outputs[i], output_x, output_y, output_width, output_height);
    }
}
