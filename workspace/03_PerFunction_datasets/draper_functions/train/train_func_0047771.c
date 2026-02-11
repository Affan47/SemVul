gst_h264_parse_get_timestamp (GstH264Parse * h264parse,
    GstClockTime * out_ts, GstClockTime * out_dur, gboolean frame)
{
  GstH264SPS *sps = h264parse->nalparser->last_sps;
  GstClockTime upstream;
  gint duration = 1;

  g_return_if_fail (out_dur != NULL);
  g_return_if_fail (out_ts != NULL);

  upstream = *out_ts;

  if (!frame) {
    GST_LOG_OBJECT (h264parse, "no frame data ->  0 duration");
    *out_dur = 0;
    goto exit;
  } else {
    *out_ts = upstream;
  }

  if (!sps) {
    GST_DEBUG_OBJECT (h264parse, "referred SPS invalid");
    goto exit;
  } else if (!sps->vui_parameters.timing_info_present_flag) {
    GST_DEBUG_OBJECT (h264parse,
        "unable to compute timestamp: timing info not present");
    goto exit;
  } else if (sps->vui_parameters.time_scale == 0) {
    GST_DEBUG_OBJECT (h264parse,
        "unable to compute timestamp: time_scale = 0 "
        "(this is forbidden in spec; bitstream probably contains error)");
    goto exit;
  }

  if (h264parse->sei_pic_struct_pres_flag &&
      h264parse->sei_pic_struct != (guint8) - 1) {


    switch (h264parse->sei_pic_struct) {
      case GST_H264_SEI_PIC_STRUCT_TOP_FIELD:
      case GST_H264_SEI_PIC_STRUCT_BOTTOM_FIELD:
        duration = 1;
        break;
      case GST_H264_SEI_PIC_STRUCT_FRAME:
      case GST_H264_SEI_PIC_STRUCT_TOP_BOTTOM:
      case GST_H264_SEI_PIC_STRUCT_BOTTOM_TOP:
        duration = 2;
        break;
      case GST_H264_SEI_PIC_STRUCT_TOP_BOTTOM_TOP:
      case GST_H264_SEI_PIC_STRUCT_BOTTOM_TOP_BOTTOM:
        duration = 3;
        break;
      case GST_H264_SEI_PIC_STRUCT_FRAME_DOUBLING:
        duration = 4;
        break;
      case GST_H264_SEI_PIC_STRUCT_FRAME_TRIPLING:
        duration = 6;
        break;
      default:
        GST_DEBUG_OBJECT (h264parse,
            "h264parse->sei_pic_struct of unknown value %d. Not parsed",
            h264parse->sei_pic_struct);
        break;
    }
  } else {
    duration = h264parse->field_pic_flag ? 1 : 2;
  }

  GST_LOG_OBJECT (h264parse, "frame tick duration %d", duration);


  if (h264parse->ts_trn_nb != GST_CLOCK_TIME_NONE) {
    GST_LOG_OBJECT (h264parse, "buffering based ts");

    if (upstream != GST_CLOCK_TIME_NONE) {


      h264parse->ts_trn_nb = upstream -
          (GstClockTime) gst_util_uint64_scale_int
          (h264parse->sei_cpb_removal_delay * GST_SECOND,
          sps->vui_parameters.num_units_in_tick,
          sps->vui_parameters.time_scale);
    } else {

      upstream = h264parse->dts = h264parse->ts_trn_nb +
          (GstClockTime) gst_util_uint64_scale_int
          (h264parse->sei_cpb_removal_delay * GST_SECOND,
          sps->vui_parameters.num_units_in_tick,
          sps->vui_parameters.time_scale);
    }
  } else {
    GstClockTime dur;

    GST_LOG_OBJECT (h264parse, "duration based ts");


    dur = gst_util_uint64_scale_int (duration * GST_SECOND,
        sps->vui_parameters.num_units_in_tick, sps->vui_parameters.time_scale);

    if (dur < GST_MSECOND) {
      GST_DEBUG_OBJECT (h264parse, "discarding dur %" GST_TIME_FORMAT,
          GST_TIME_ARGS (dur));
    } else {
      *out_dur = dur;
    }
  }

exit:
  if (GST_CLOCK_TIME_IS_VALID (upstream))
    *out_ts = h264parse->dts = upstream;

  if (GST_CLOCK_TIME_IS_VALID (*out_dur) &&
      GST_CLOCK_TIME_IS_VALID (h264parse->dts))
    h264parse->dts += *out_dur;
}
