on_resolution_changed (GtkComboBox *box, gpointer data)
{
  CcDisplayPanel *self = data;
  int old_width, old_height;
  int x,y;
  int width;
  int height;

  if (!self->priv->current_output)
    return;

  gnome_rr_output_info_get_geometry (self->priv->current_output, &x, &y, &old_width, &old_height);

  if (get_mode (self->priv->resolution_combo, &width, &height, NULL, NULL))
    {
      gnome_rr_output_info_set_geometry (self->priv->current_output, x, y, width, height);

      if (width == 0 || height == 0)
        gnome_rr_output_info_set_active (self->priv->current_output, FALSE);
      else
        gnome_rr_output_info_set_active (self->priv->current_output, TRUE);
    }

  realign_outputs_after_resolution_change (self, self->priv->current_output, old_width, old_height);

  rebuild_rotation_combo (self);

  foo_scroll_area_invalidate (FOO_SCROLL_AREA (self->priv->area));
}
