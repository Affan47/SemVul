gst_flv_demux_cleanup (GstFlvDemux * demux)
{
  GST_DEBUG_OBJECT (demux, "cleaning up FLV demuxer");

  demux->state = FLV_STATE_HEADER;

  demux->have_group_id = FALSE;
  demux->group_id = G_MAXUINT;

  demux->flushing = FALSE;
  demux->need_header = TRUE;
  demux->audio_need_segment = TRUE;
  demux->video_need_segment = TRUE;
  demux->audio_need_discont = TRUE;
  demux->video_need_discont = TRUE;


  demux->audio_linked = TRUE;
  demux->video_linked = TRUE;

  demux->has_audio = FALSE;
  demux->has_video = FALSE;
  demux->push_tags = FALSE;
  demux->got_par = FALSE;

  demux->indexed = FALSE;
  demux->upstream_seekable = FALSE;
  demux->file_size = 0;

  demux->index_max_pos = 0;
  demux->index_max_time = 0;

  demux->audio_start = demux->video_start = GST_CLOCK_TIME_NONE;
  demux->last_audio_pts = demux->last_video_pts = 0;
  demux->audio_time_offset = demux->video_time_offset = 0;

  demux->no_more_pads = FALSE;

  gst_segment_init (&demux->segment, GST_FORMAT_TIME);

  demux->w = demux->h = 0;
  demux->framerate = 0.0;
  demux->par_x = demux->par_y = 1;
  demux->video_offset = 0;
  demux->audio_offset = 0;
  demux->offset = demux->cur_tag_offset = 0;
  demux->tag_size = demux->tag_data_size = 0;
  demux->duration = GST_CLOCK_TIME_NONE;

  if (demux->new_seg_event) {
    gst_event_unref (demux->new_seg_event);
    demux->new_seg_event = NULL;
  }

  gst_adapter_clear (demux->adapter);

  if (demux->audio_codec_data) {
    gst_buffer_unref (demux->audio_codec_data);
    demux->audio_codec_data = NULL;
  }

  if (demux->video_codec_data) {
    gst_buffer_unref (demux->video_codec_data);
    demux->video_codec_data = NULL;
  }

  if (demux->audio_pad) {
    gst_element_remove_pad (GST_ELEMENT (demux), demux->audio_pad);
    gst_object_unref (demux->audio_pad);
    demux->audio_pad = NULL;
  }

  if (demux->video_pad) {
    gst_element_remove_pad (GST_ELEMENT (demux), demux->video_pad);
    gst_object_unref (demux->video_pad);
    demux->video_pad = NULL;
  }

  if (demux->times) {
    g_array_free (demux->times, TRUE);
    demux->times = NULL;
  }

  if (demux->filepositions) {
    g_array_free (demux->filepositions, TRUE);
    demux->filepositions = NULL;
  }
}
