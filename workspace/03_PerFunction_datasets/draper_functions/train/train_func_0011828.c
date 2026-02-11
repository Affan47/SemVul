gst_matroska_read_common_reset_streams (GstMatroskaReadCommon * common,
    GstClockTime time, gboolean full)
{
  gint i;

  GST_DEBUG_OBJECT (common, "resetting stream state");

  g_assert (common->src->len == common->num_streams);
  for (i = 0; i < common->src->len; i++) {
    GstMatroskaTrackContext *context = g_ptr_array_index (common->src, i);
    context->pos = time;
    context->set_discont = TRUE;
    context->eos = FALSE;
    context->from_time = GST_CLOCK_TIME_NONE;
    if (full)
      context->last_flow = GST_FLOW_OK;
    if (context->type == GST_MATROSKA_TRACK_TYPE_VIDEO) {
      GstMatroskaTrackVideoContext *videocontext =
          (GstMatroskaTrackVideoContext *) context;

      videocontext->earliest_time = GST_CLOCK_TIME_NONE;
    }
  }
}
