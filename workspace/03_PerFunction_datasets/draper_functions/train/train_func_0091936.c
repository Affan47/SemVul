gst_base_audio_src_query (GstBaseSrc * bsrc, GstQuery * query)
{
  GstBaseAudioSrc *src = GST_BASE_AUDIO_SRC (bsrc);
  gboolean res = FALSE;

  switch (GST_QUERY_TYPE (query)) {
    case GST_QUERY_LATENCY:
    {
      GstClockTime min_latency, max_latency;
      GstRingBufferSpec *spec;

      GST_OBJECT_LOCK (src);
      if (G_UNLIKELY (src->ringbuffer == NULL
              || src->ringbuffer->spec.rate == 0)) {
        GST_OBJECT_UNLOCK (src);
        goto done;
      }

      spec = &src->ringbuffer->spec;


      min_latency =
          gst_util_uint64_scale_int (spec->segsize, GST_SECOND,
          spec->rate * spec->bytes_per_sample);

      max_latency =
          gst_util_uint64_scale_int (spec->segtotal * spec->segsize, GST_SECOND,
          spec->rate * spec->bytes_per_sample);
      GST_OBJECT_UNLOCK (src);

      GST_DEBUG_OBJECT (src,
          "report latency min %" GST_TIME_FORMAT " max %" GST_TIME_FORMAT,
          GST_TIME_ARGS (min_latency), GST_TIME_ARGS (max_latency));


      gst_query_set_latency (query, TRUE, min_latency, max_latency);

      res = TRUE;
      break;
    }
    default:
      res = GST_BASE_SRC_CLASS (parent_class)->query (bsrc, query);
      break;
  }
done:
  return res;
}
