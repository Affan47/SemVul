for_each_threshold_by_entry (gpointer data, gpointer user_data)
{
  GstDebugCategory *cat = (GstDebugCategory *) data;
  LevelNameEntry *entry = (LevelNameEntry *) user_data;

  if (g_pattern_match_string (entry->pat, cat->name)) {
    GST_LOG ("category %s matches pattern %p - gets set to level %d",
        cat->name, entry->pat, entry->level);
    gst_debug_category_set_threshold (cat, entry->level);
  }
}
