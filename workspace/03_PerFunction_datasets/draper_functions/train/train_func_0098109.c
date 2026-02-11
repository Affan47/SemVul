gst_debug_compare_log_function_by_data (gconstpointer entry, gconstpointer data)
{
  gpointer entrydata = ((LogFuncEntry *) entry)->user_data;

  return (entrydata < data) ? -1 : (entrydata > data) ? 1 : 0;
}
