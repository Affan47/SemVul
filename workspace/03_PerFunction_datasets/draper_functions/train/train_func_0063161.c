push_event (MpegTSBase * base, GstEvent * event)
{
  GstTSDemux *demux = (GstTSDemux *) base;
  GList *tmp;

  if (G_UNLIKELY (demux->program == NULL))
    return FALSE;

  for (tmp = demux->program->stream_list; tmp; tmp = tmp->next) {
    TSDemuxStream *stream = (TSDemuxStream *) tmp->data;
    if (stream->pad) {
      gst_event_ref (event);
      gst_pad_push_event (stream->pad, event);
    }
  }

  return TRUE;
}
