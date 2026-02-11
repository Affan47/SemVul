gst_flv_mux_reset (GstElement * element)
{
  GstFlvMux *mux = GST_FLV_MUX (element);
  GSList *sl;

  for (sl = mux->collect->data; sl != NULL; sl = g_slist_next (sl)) {
    GstFlvPad *cpad = (GstFlvPad *) sl->data;

    gst_flv_mux_reset_pad (mux, cpad, cpad->video);
  }

  g_list_foreach (mux->index, (GFunc) gst_flv_mux_index_entry_free, NULL);
  g_list_free (mux->index);
  mux->index = NULL;
  mux->byte_count = 0;

  mux->have_audio = mux->have_video = FALSE;
  mux->duration = GST_CLOCK_TIME_NONE;
  mux->new_tags = FALSE;

  mux->state = GST_FLV_MUX_STATE_HEADER;


  gst_tag_setter_reset_tags (GST_TAG_SETTER (mux));
}
