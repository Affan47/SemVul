gst_sample_new (GstBuffer * buffer, GstCaps * caps, const GstSegment * segment,
    GstStructure * info)
{
  GstSample *sample;

  sample = g_slice_new0 (GstSample);

  GST_LOG ("new %p", sample);

  gst_mini_object_init (GST_MINI_OBJECT_CAST (sample), 0, _gst_sample_type,
      (GstMiniObjectCopyFunction) _gst_sample_copy, NULL,
      (GstMiniObjectFreeFunction) _gst_sample_free);

  sample->buffer = buffer ? gst_buffer_ref (buffer) : NULL;
  sample->caps = caps ? gst_caps_ref (caps) : NULL;

  if (segment)
    gst_segment_copy_into (segment, &sample->segment);
  else
    gst_segment_init (&sample->segment, GST_FORMAT_TIME);

  if (info) {
    if (!gst_structure_set_parent_refcount (info,
            &sample->mini_object.refcount))
      goto had_parent;

    sample->info = info;
  }
  return sample;


had_parent:
  {
    gst_sample_unref (sample);
    g_warning ("structure is already owned by another object");
    return NULL;
  }
}
