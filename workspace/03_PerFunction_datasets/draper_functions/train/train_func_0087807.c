_gst_clock_id_free (GstClockID id)
{
  GstClockEntry *entry;
  g_return_if_fail (id != NULL);

  GST_CAT_DEBUG (GST_CAT_CLOCK, "freed entry %p", id);
  entry = (GstClockEntry *) id;
  if (entry->destroy_data)
    entry->destroy_data (entry->user_data);

#ifndef GST_DISABLE_TRACE
  _gst_alloc_trace_free (_gst_clock_entry_trace, id);
#endif
  g_slice_free (GstClockEntry, id);
}
