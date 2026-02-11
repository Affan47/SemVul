gst_audio_cd_src_make_toc (GstAudioCdSrc * src, GstTocScope scope)
{
  GstToc *toc;
  gint i;

  toc = gst_toc_new (scope);

  for (i = 0; i < src->priv->num_tracks; ++i) {
    GstAudioCdSrcTrack *track;
    gint64 start_time, stop_time;
    GstTocEntry *entry;
    gchar *uid;

    track = &src->priv->tracks[i];


    uid = g_strdup_printf ("audiocd-track-%03u", track->num);
    entry = gst_toc_entry_new (GST_TOC_ENTRY_TYPE_TRACK, uid);
    gst_toc_entry_set_tags (entry, gst_tag_list_ref (track->tags));

    gst_audio_cd_src_convert (src, sector_format, track->start,
        GST_FORMAT_TIME, &start_time);
    gst_audio_cd_src_convert (src, sector_format, track->end + 1,
        GST_FORMAT_TIME, &stop_time);

    GST_INFO ("Track %03u  %" GST_TIME_FORMAT " - %" GST_TIME_FORMAT,
        track->num, GST_TIME_ARGS (start_time), GST_TIME_ARGS (stop_time));

    gst_toc_entry_set_start_stop_times (entry, start_time, stop_time);
    gst_toc_append_entry (toc, entry);
    g_free (uid);
  }

  return toc;
}
