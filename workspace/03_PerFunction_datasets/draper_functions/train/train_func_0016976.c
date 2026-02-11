gst_wavparse_reset (GstWavParse * wav)
{
  wav->state = GST_WAVPARSE_START;


  wav->depth = 0;
  wav->rate = 0;
  wav->width = 0;
  wav->channels = 0;
  wav->blockalign = 0;
  wav->bps = 0;
  wav->fact = 0;
  wav->offset = 0;
  wav->end_offset = 0;
  wav->dataleft = 0;
  wav->datasize = 0;
  wav->datastart = 0;
  wav->duration = 0;
  wav->got_fmt = FALSE;
  wav->first = TRUE;

  if (wav->seek_event)
    gst_event_unref (wav->seek_event);
  wav->seek_event = NULL;
  if (wav->adapter) {
    gst_adapter_clear (wav->adapter);
    g_object_unref (wav->adapter);
    wav->adapter = NULL;
  }
  if (wav->tags)
    gst_tag_list_unref (wav->tags);
  wav->tags = NULL;
  if (wav->toc)
    gst_toc_unref (wav->toc);
  wav->toc = NULL;
  if (wav->cues)
    g_list_free_full (wav->cues, g_free);
  wav->cues = NULL;
  if (wav->labls)
    g_list_free_full (wav->labls, g_free);
  wav->labls = NULL;
  if (wav->caps)
    gst_caps_unref (wav->caps);
  wav->caps = NULL;
  if (wav->start_segment)
    gst_event_unref (wav->start_segment);
  wav->start_segment = NULL;
}
