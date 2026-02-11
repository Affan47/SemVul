gst_play_bin_vis_unblocked (GstPad * tee_pad, gboolean blocked,
    gpointer user_data)
{
  GstPlayBin *play_bin = GST_PLAY_BIN (user_data);

  if (play_bin->pending_visualisation)
    gst_pad_set_blocked_async (tee_pad, FALSE, gst_play_bin_vis_unblocked,
        play_bin);
}
