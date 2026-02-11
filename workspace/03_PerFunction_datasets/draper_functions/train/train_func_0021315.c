mpegtsmux_dispose (GObject * object)
{
  MpegTsMux *mux = GST_MPEG_TSMUX (object);

  if (mux->adapter) {
    gst_adapter_clear (mux->adapter);
    g_object_unref (mux->adapter);
    mux->adapter = NULL;
  }
  if (mux->collect) {
    gst_object_unref (mux->collect);
    mux->collect = NULL;
  }
  if (mux->tsmux) {
    tsmux_free (mux->tsmux);
    mux->tsmux = NULL;
  }
  if (mux->prog_map) {
    gst_structure_free (mux->prog_map);
    mux->prog_map = NULL;
  }
  if (mux->programs) {
    g_free (mux->programs);
    mux->programs = NULL;
  }
  if (mux->streamheader) {
    GstBuffer *buf;
    GList *sh;

    sh = mux->streamheader;
    while (sh) {
      buf = sh->data;
      gst_buffer_unref (buf);
      sh = g_list_next (sh);
    }
    g_list_free (mux->streamheader);
    mux->streamheader = NULL;
  }
  GST_CALL_PARENT (G_OBJECT_CLASS, dispose, (object));
}
