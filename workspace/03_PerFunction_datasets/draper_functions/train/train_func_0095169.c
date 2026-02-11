push_event (MpegTSBase * base, GstEvent * event)
{
  MpegTSParse2 *parse = (MpegTSParse2 *) base;
  GList *tmp;

  if (G_UNLIKELY (parse->first)) {

    if (G_UNLIKELY (GST_EVENT_TYPE (event) == GST_EVENT_SEGMENT)) {
      gst_event_unref (event);
      return TRUE;
    }
    prepare_src_pad (base, parse);
  }

  for (tmp = parse->srcpads; tmp; tmp = tmp->next) {
    GstPad *pad = (GstPad *) tmp->data;
    if (pad) {
      gst_event_ref (event);
      gst_pad_push_event (pad, event);
    }
  }

  gst_pad_push_event (parse->srcpad, event);

  return TRUE;
}
