gst_ogg_stream_granule_to_time (GstOggStream * pad, gint64 granule)
{
  if (granule == 0 || pad->granulerate_n == 0 || pad->granulerate_d == 0)
    return 0;

  granule += pad->granule_offset;
  if (granule < 0)
    return 0;

  return gst_util_uint64_scale (granule, GST_SECOND * pad->granulerate_d,
      pad->granulerate_n);
}
