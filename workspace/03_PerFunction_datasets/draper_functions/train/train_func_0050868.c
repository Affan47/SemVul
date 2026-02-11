gst_matroska_mux_track_header (GstMatroskaMux * mux,
    GstMatroskaTrackContext * context)
{
  GstEbmlWrite *ebml = mux->ebml_write;
  guint64 master;


  gst_ebml_write_uint (ebml, GST_MATROSKA_ID_TRACKNUMBER, context->num);
  gst_ebml_write_uint (ebml, GST_MATROSKA_ID_TRACKTYPE, context->type);

  gst_ebml_write_uint (ebml, GST_MATROSKA_ID_TRACKUID,
      gst_matroska_mux_create_uid ());
  if (context->default_duration) {
    gst_ebml_write_uint (ebml, GST_MATROSKA_ID_TRACKDEFAULTDURATION,
        context->default_duration);
  }
  if (context->language) {
    gst_ebml_write_utf8 (ebml, GST_MATROSKA_ID_TRACKLANGUAGE,
        context->language);
  }


  gst_ebml_write_utf8 (ebml, GST_MATROSKA_ID_TRACKNAME, context->name);


  switch (context->type) {
    case GST_MATROSKA_TRACK_TYPE_VIDEO:{
      GstMatroskaTrackVideoContext *videocontext =
          (GstMatroskaTrackVideoContext *) context;

      master = gst_ebml_write_master_start (ebml, GST_MATROSKA_ID_TRACKVIDEO);
      gst_ebml_write_uint (ebml, GST_MATROSKA_ID_VIDEOPIXELWIDTH,
          videocontext->pixel_width);
      gst_ebml_write_uint (ebml, GST_MATROSKA_ID_VIDEOPIXELHEIGHT,
          videocontext->pixel_height);
      if (videocontext->display_width && videocontext->display_height) {
        gst_ebml_write_uint (ebml, GST_MATROSKA_ID_VIDEODISPLAYWIDTH,
            videocontext->display_width);
        gst_ebml_write_uint (ebml, GST_MATROSKA_ID_VIDEODISPLAYHEIGHT,
            videocontext->display_height);
      }
      if (context->flags & GST_MATROSKA_VIDEOTRACK_INTERLACED)
        gst_ebml_write_uint (ebml, GST_MATROSKA_ID_VIDEOFLAGINTERLACED, 1);
      if (videocontext->fourcc) {
        guint32 fcc_le = GUINT32_TO_LE (videocontext->fourcc);

        gst_ebml_write_binary (ebml, GST_MATROSKA_ID_VIDEOCOLOURSPACE,
            (gpointer) & fcc_le, 4);
      }
      gst_ebml_write_master_finish (ebml, master);

      break;
    }

    case GST_MATROSKA_TRACK_TYPE_AUDIO:{
      GstMatroskaTrackAudioContext *audiocontext =
          (GstMatroskaTrackAudioContext *) context;

      master = gst_ebml_write_master_start (ebml, GST_MATROSKA_ID_TRACKAUDIO);
      if (audiocontext->samplerate != 8000)
        gst_ebml_write_float (ebml, GST_MATROSKA_ID_AUDIOSAMPLINGFREQ,
            audiocontext->samplerate);
      if (audiocontext->channels != 1)
        gst_ebml_write_uint (ebml, GST_MATROSKA_ID_AUDIOCHANNELS,
            audiocontext->channels);
      if (audiocontext->bitdepth) {
        gst_ebml_write_uint (ebml, GST_MATROSKA_ID_AUDIOBITDEPTH,
            audiocontext->bitdepth);
      }
      gst_ebml_write_master_finish (ebml, master);

      break;
    }

    case GST_MATROSKA_TRACK_TYPE_SUBTITLE:{
      break;
    }
    default:

      break;
  }

  gst_ebml_write_ascii (ebml, GST_MATROSKA_ID_CODECID, context->codec_id);
  if (context->codec_priv)
    gst_ebml_write_binary (ebml, GST_MATROSKA_ID_CODECPRIVATE,
        context->codec_priv, context->codec_priv_size);
}
