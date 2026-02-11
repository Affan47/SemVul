gst_gnome_vfs_sink_stop (GstBaseSink * basesink)
{
  GST_DEBUG_OBJECT (basesink, "closing ...");
  gst_gnome_vfs_sink_close_file (GST_GNOME_VFS_SINK (basesink));
  return TRUE;
}
