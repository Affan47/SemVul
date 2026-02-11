libgnac_gst_stop(LibgnacMediaItem  *item,
                 GError           **error)
{
  g_return_if_fail(!error || !*error);

  if (!item) return;

  if (item->pipeline) {
    libgnac_gst_clean_pipeline(item);
  }
}
