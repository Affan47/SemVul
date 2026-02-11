handle_material_track(bgav_demuxer_context_t * ctx, mxf_package_t * p,
                                  mxf_track_t * mt, bgav_edl_track_t * et)
  {
  int i;
  mxf_sequence_t * ss;
  mxf_source_clip_t * sc;
  mxf_t * priv;
  bgav_edl_stream_t * es = NULL;
  int track_index, stream_index = 0;
  bgav_edl_segment_t * seg;
  int64_t duration = 0;
  priv = ctx->priv;

  if(!mt)
    return;

  ss = (mxf_sequence_t*)(mt->sequence);

  if(!ss)
    return;

  if(ss->is_timecode)
    {

    return;
    }
  else if(ss->stream_type == BGAV_STREAM_UNKNOWN)
    {
    return;
    }
  else
    {
    if(!ss->structural_components ||
       (ss->structural_components[0]->type != MXF_TYPE_SOURCE_CLIP))
      return;

    es = NULL;

    switch(ss->stream_type)
      {
      case BGAV_STREAM_AUDIO:
        es = bgav_edl_add_audio_stream(et);
        break;
      case BGAV_STREAM_VIDEO:
        es = bgav_edl_add_video_stream(et);
        break;
      case BGAV_STREAM_SUBTITLE_TEXT:
      case BGAV_STREAM_SUBTITLE_OVERLAY:
      case BGAV_STREAM_UNKNOWN:
        break;
      }
    if(!es)
      return;

    es->timescale = mt->edit_rate_num;

    for(i = 0; i < ss->num_structural_component_refs; i++)
      {
      sc = (mxf_source_clip_t*)(ss->structural_components[i]);


      if(get_source_stream(ctx->tt,
                            &priv->mxf,
                            &track_index, &stream_index,
                            ss->stream_type,
                            (mxf_package_t*)sc->source_package,
                            sc->source_track_id))
        {
        seg = bgav_edl_add_segment(es);
        seg->track        = track_index;
        seg->stream       = stream_index;
        seg->timescale    = mt->edit_rate_num;
        seg->src_time     = sc->start_position * mt->edit_rate_den;
        seg->dst_time     = duration;
        seg->dst_duration = sc->duration * mt->edit_rate_den;
        seg->speed_num    = 1;
        seg->speed_den    = 1;
        }

      duration += sc->duration * mt->edit_rate_den;
      }
    }
  }
