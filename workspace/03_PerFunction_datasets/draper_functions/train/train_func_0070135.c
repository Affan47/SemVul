on_devtab_action_partition_create_activated (GtkAction *action,
                                             gpointer   user_data)
{
  GduWindow *window = GDU_WINDOW (user_data);
  UDisksObject *object;

  object = gdu_volume_grid_get_block_object (GDU_VOLUME_GRID (window->volume_grid));
  g_assert (object != NULL);
  gdu_create_partition_dialog_show (window,
                                    object,
                                    gdu_volume_grid_get_selected_offset (GDU_VOLUME_GRID (window->volume_grid)),
                                    gdu_volume_grid_get_selected_size (GDU_VOLUME_GRID (window->volume_grid)));
}
