gst_avi_mux_reset (GstAviMux * avimux)
{
  GSList *node, *newlist = NULL;


  node = avimux->sinkpads;
  while (node) {
    GstAviPad *avipad = (GstAviPad *) node->data;

    node = node->next;

    gst_avi_mux_pad_reset (avipad, FALSE);

    if (avipad->collect)
      newlist = g_slist_append (newlist, avipad);
    else {
      gst_avi_mux_pad_reset (avipad, TRUE);
      g_free (avipad);
    }
  }


  g_slist_free (avimux->sinkpads);
  avimux->sinkpads = newlist;


  avimux->num_frames = 0;
  memset (&(avimux->avi_hdr), 0, sizeof (gst_riff_avih));
  avimux->avi_hdr.max_bps = 10000000;
  avimux->codec_data_size = 0;

  if (avimux->tags_snap) {
    gst_tag_list_unref (avimux->tags_snap);
    avimux->tags_snap = NULL;
  }

  g_free (avimux->idx);
  avimux->idx = NULL;


  avimux->write_header = TRUE;


  gst_tag_setter_reset_tags (GST_TAG_SETTER (avimux));
}
