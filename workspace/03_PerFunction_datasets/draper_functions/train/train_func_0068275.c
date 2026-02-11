gst_system_clock_dispose (GObject * object)
{
  GstClock *clock = (GstClock *) object;
  GstSystemClock *sysclock = GST_SYSTEM_CLOCK_CAST (clock);
  GstSystemClockPrivate *priv = sysclock->priv;
  GList *entries;


  GST_OBJECT_LOCK (clock);
  priv->stopping = TRUE;

  for (entries = priv->entries; entries; entries = g_list_next (entries)) {
    GstClockEntry *entry = (GstClockEntry *) entries->data;

    GST_CAT_DEBUG (GST_CAT_CLOCK, "unscheduling entry %p", entry);
    SET_ENTRY_STATUS (entry, GST_CLOCK_UNSCHEDULED);
  }
  GST_SYSTEM_CLOCK_BROADCAST (clock);
  gst_system_clock_add_wakeup (sysclock);
  GST_OBJECT_UNLOCK (clock);

  if (priv->thread)
    g_thread_join (priv->thread);
  priv->thread = NULL;
  GST_CAT_DEBUG (GST_CAT_CLOCK, "joined thread");

  g_list_foreach (priv->entries, (GFunc) gst_clock_id_unref, NULL);
  g_list_free (priv->entries);
  priv->entries = NULL;

  gst_poll_free (priv->timer);
  g_cond_clear (&priv->entries_changed);

  G_OBJECT_CLASS (parent_class)->dispose (object);

  if (_the_system_clock == clock) {
    _the_system_clock = NULL;
    GST_CAT_DEBUG (GST_CAT_CLOCK, "disposed system clock");
  }
}
