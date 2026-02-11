gst_multipart_demux_get_gstname (GstMultipartDemux * demux, gchar * mimetype)
{
  GstMultipartDemuxClass *klass;
  const gchar *gstname;

  klass = GST_MULTIPART_DEMUX_GET_CLASS (demux);


  gstname = g_hash_table_lookup (klass->gstnames, mimetype);
  if (gstname == NULL) {

    gstname = mimetype;
  }
  GST_DEBUG_OBJECT (demux, "gst name for %s is %s", mimetype, gstname);
  return gstname;
}
