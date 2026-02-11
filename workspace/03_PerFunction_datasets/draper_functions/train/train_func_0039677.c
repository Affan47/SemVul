gst_matroska_mux_reset (GstElement * element)
{
  GstMatroskaMux *mux = GST_MATROSKA_MUX (element);
  GSList *walk;


  gst_ebml_write_reset (mux->ebml_write);


  mux->state = GST_MATROSKA_MUX_STATE_START;


  for (walk = mux->collect->data; walk; walk = g_slist_next (walk)) {
    GstMatroskaPad *collect_pad;

    collect_pad = (GstMatroskaPad *) walk->data;


    gst_matroska_pad_reset (collect_pad, FALSE);
  }


  mux->num_indexes = 0;
  g_free (mux->index);
  mux->index = NULL;


  mux->time_scale = GST_MSECOND;
  mux->max_cluster_duration = G_MAXINT16 * mux->time_scale;
  mux->duration = 0;


  mux->cluster = 0;
  mux->cluster_time = 0;
  mux->cluster_pos = 0;
  mux->prev_cluster_size = 0;


  gst_tag_setter_reset_tags (GST_TAG_SETTER (mux));

  mux->tags_pos = 0;


  gst_toc_setter_reset (GST_TOC_SETTER (mux));

  mux->chapters_pos = 0;
}
