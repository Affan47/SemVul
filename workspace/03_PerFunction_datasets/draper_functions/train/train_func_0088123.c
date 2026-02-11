gst_cmml_track_list_destroy_track (gchar * key,
    GstCmmlTrack * track, gpointer user_data)
{
  GList *walk;

  for (walk = track->clips; walk; walk = g_list_next (walk))
    g_object_unref (G_OBJECT (walk->data));

  g_free (key);
  g_list_free (track->clips);
  g_free (track);

  return TRUE;
}
