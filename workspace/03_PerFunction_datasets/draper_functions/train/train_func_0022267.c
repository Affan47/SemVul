mpegpsmux_choose_best_stream (MpegPsMux * mux)
{


  MpegPsPadData *best = NULL;
  GstCollectData *c_best = NULL;
  GSList *walk;

  for (walk = mux->collect->data; walk != NULL; walk = g_slist_next (walk)) {
    GstCollectData *c_data = (GstCollectData *) walk->data;
    MpegPsPadData *ps_data = (MpegPsPadData *) walk->data;

    if (ps_data->eos == FALSE) {
      if (ps_data->queued.buf == NULL) {
        GstBuffer *buf;

        buf = mpegpsmux_queue_buffer_for_stream (mux, ps_data);
        if (buf == NULL) {
          ps_data->eos = TRUE;
          continue;
        }


        if (ps_data->last_ts == GST_CLOCK_TIME_NONE) {
          best = ps_data;
          c_best = c_data;
        }
      }


      if (best != NULL) {
        if (ps_data->last_ts != GST_CLOCK_TIME_NONE &&
            best->last_ts != GST_CLOCK_TIME_NONE &&
            ps_data->last_ts < best->last_ts) {
          best = ps_data;
          c_best = c_data;
        }
      } else {
        best = ps_data;
        c_best = c_data;
      }
    }
  }
  if (c_best) {
    gst_buffer_unref (gst_collect_pads_pop (mux->collect, c_best));
  }

  return best;
}
