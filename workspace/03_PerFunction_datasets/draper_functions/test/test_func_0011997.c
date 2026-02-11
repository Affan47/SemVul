atk_remove_focus_tracker (guint            tracker_id)
{
  FocusTracker *item;
  guint i;

  if (trackers == NULL)
    return;

  if (tracker_id == 0)
    return;

  for (i = 0; i < trackers->len; i++)
  {
    item = &g_array_index (trackers, FocusTracker, i);
    if (item->index == tracker_id)
    {
      trackers = g_array_remove_index (trackers, i);
      break;
    }
  }
}
