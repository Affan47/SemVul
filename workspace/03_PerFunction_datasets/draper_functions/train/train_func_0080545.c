free_queue_redraw_entry (ClutterStageQueueRedrawEntry *entry)
{
  if (entry->actor)
    g_object_unref (entry->actor);
  if (entry->has_clip)
    clutter_paint_volume_free (&entry->clip);
  g_slice_free (ClutterStageQueueRedrawEntry, entry);
}
