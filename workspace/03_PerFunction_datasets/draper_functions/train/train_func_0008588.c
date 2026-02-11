gst_linsys_sdi_src_start (GstBaseSrc * src)
{
  GstLinsysSdiSrc *linsyssdisrc = GST_LINSYS_SDI_SRC (src);
  int fd;

  GST_DEBUG_OBJECT (linsyssdisrc, "start");

  fd = open (linsyssdisrc->device, O_RDONLY);
  if (fd < 0) {
    GST_ERROR_OBJECT (src, "failed to open device");
    return FALSE;
  }

  linsyssdisrc->fd = fd;

  if (linsyssdisrc->is_625) {
    linsyssdisrc->tmpdata = g_malloc (864 * 625 * 2);
  } else {
    linsyssdisrc->tmpdata = g_malloc (858 * 525 * 2);
  }
  linsyssdisrc->have_sync = FALSE;

  return TRUE;
}
