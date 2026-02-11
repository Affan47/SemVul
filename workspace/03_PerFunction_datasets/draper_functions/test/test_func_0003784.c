gst_avi_mux_stop_file (GstAviMux * avimux)
{
  GstFlowReturn res = GST_FLOW_OK;
  GstBuffer *header;
  GSList *node;
  GstSegment segment;


  if (avimux->video_pads > 0) {
    if (avimux->is_bigfile) {
      res = gst_avi_mux_bigfile (avimux, TRUE);
    } else {
      res = gst_avi_mux_write_index (avimux);
    }
  }


  if (avimux->audio_pads > 0 && avimux->video_pads > 0)
    avimux->avi_hdr.flags |= GST_RIFF_AVIH_ISINTERLEAVED;


  avimux->avi_hdr.max_bps = 0;
  node = avimux->sinkpads;
  while (node) {
    GstAviPad *avipad = (GstAviPad *) node->data;

    node = node->next;

    if (!avipad->is_video) {
      GstAviAudioPad *audpad = (GstAviAudioPad *) avipad;


      if (!audpad->auds.av_bps) {
        if (audpad->audio_time) {
          audpad->auds.av_bps =
              (GST_SECOND * audpad->audio_size) / audpad->audio_time;


          audpad->auds.av_bps = GST_ROUND_UP_8 (audpad->auds.av_bps - 4);
        } else {
          GST_ELEMENT_WARNING (avimux, STREAM, MUX,
              (_("No or invalid input audio, AVI stream will be corrupt.")),
              (NULL));
          audpad->auds.av_bps = 0;
        }
      }

      if (audpad->max_audio_chunk)
        audpad->auds.blockalign = audpad->max_audio_chunk;
      gst_avi_mux_audsink_set_fields (avimux, audpad);
      avimux->avi_hdr.max_bps += audpad->auds.av_bps;
      avipad->hdr.length = gst_util_uint64_scale (audpad->audio_time,
          avipad->hdr.rate, avipad->hdr.scale * GST_SECOND);
    } else {
      GstAviVideoPad *vidpad = (GstAviVideoPad *) avipad;

      avimux->avi_hdr.max_bps += ((vidpad->vids.bit_cnt + 7) / 8) *
          (1000000. / avimux->avi_hdr.us_frame) * vidpad->vids.image_size;
      avipad->hdr.length = avimux->total_frames;
    }
  }


  avimux->avi_hdr.tot_frames = avimux->num_frames;


  gst_segment_init (&segment, GST_FORMAT_BYTES);
  gst_pad_push_event (avimux->srcpad, gst_event_new_segment (&segment));


  header = gst_avi_mux_riff_get_avi_header (avimux);
  if (res == GST_FLOW_OK)
    res = gst_pad_push (avimux->srcpad, header);
  else
    gst_pad_push (avimux->srcpad, header);

  segment.start = avimux->total_data;
  segment.time = avimux->total_data;
  gst_pad_push_event (avimux->srcpad, gst_event_new_segment (&segment));

  avimux->write_header = TRUE;

  return res;
}
