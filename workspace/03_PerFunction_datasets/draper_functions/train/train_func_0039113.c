gst_field_analysis_flush_frames (GstFieldAnalysis * filter)
{
  GQueue *outbufs;

  if (filter->nframes < 2)
    return NULL;

  outbufs = g_queue_new ();

  while (filter->nframes)
    gst_field_analysis_flush_one (filter, outbufs);

  return outbufs;
}
