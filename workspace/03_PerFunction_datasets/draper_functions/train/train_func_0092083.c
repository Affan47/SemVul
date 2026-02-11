gst_ogg_mux_init_collectpads (GstCollectPads * collect)
{
  GSList *walk;

  walk = collect->data;
  while (walk) {
    GstOggPadData *oggpad = (GstOggPadData *) walk->data;

    ogg_stream_init (&oggpad->map.stream, oggpad->map.serialno);
    oggpad->packetno = 0;
    oggpad->pageno = 0;
    oggpad->eos = FALSE;

    oggpad->state = GST_OGG_PAD_STATE_CONTROL;
    oggpad->new_page = TRUE;
    oggpad->first_delta = FALSE;
    oggpad->prev_delta = FALSE;
    oggpad->data_pushed = FALSE;
    oggpad->pagebuffers = g_queue_new ();

    gst_segment_init (&oggpad->segment, GST_FORMAT_TIME);

    walk = g_slist_next (walk);
  }
}
