gst_dvbsub_overlay_finalize (GObject * object)
{
  GstDVBSubOverlay *overlay = GST_DVBSUB_OVERLAY (object);
  DVBSubtitles *subs;

  while ((subs = g_queue_pop_head (overlay->pending_subtitles))) {
    dvb_subtitles_free (subs);
  }
  g_queue_free (overlay->pending_subtitles);

  if (overlay->current_subtitle)
    dvb_subtitles_free (overlay->current_subtitle);
  overlay->current_subtitle = NULL;

  if (overlay->dvb_sub)
    dvb_sub_free (overlay->dvb_sub);

  if (overlay->dvbsub_mutex)
    g_mutex_free (overlay->dvbsub_mutex);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}
