setup_substreams (GstPlayBaseBin * play_base_bin)
{
  GstPlayBaseGroup *group;
  gint n;
  const GList *item;

  GST_DEBUG_OBJECT (play_base_bin, "setting up substreams");


  group = get_active_group (play_base_bin);
  for (item = group->streaminfo; item; item = item->next) {
    GstStreamInfo *info = item->data;
    gpointer data;

    data = g_object_get_data (G_OBJECT (info->object), "eat_probe");
    if (data) {
      gst_pad_remove_data_probe (GST_PAD_CAST (info->object),
          GPOINTER_TO_INT (data));
      g_object_set_data (G_OBJECT (info->object), "eat_probe", NULL);
    }


    if (info->type == GST_STREAM_TYPE_UNKNOWN) {
      guint id;

      id = GPOINTER_TO_INT (g_object_get_data (G_OBJECT (info), "mute_probe"));
      if (id == 0) {
        id = gst_pad_add_buffer_probe (GST_PAD_CAST (info->object),
            G_CALLBACK (mute_stream), info);
        g_object_set_data (G_OBJECT (info), "mute_probe", GINT_TO_POINTER (id));
      }
    }
  }


  for (n = 0; n < NUM_TYPES; n++) {
    if (play_base_bin->current[n] >= group->type[n].npads) {
      GST_DEBUG_OBJECT (play_base_bin, "reset type %d to current 0", n);
      play_base_bin->current[n] = 0;
    }
  }


  for (n = 0; n < NUM_TYPES; n++) {
    GST_DEBUG_OBJECT (play_base_bin, "setting type %d to current %d", n,
        play_base_bin->current[n]);
    set_active_source (play_base_bin, n + 1, play_base_bin->current[n]);
  }
}
