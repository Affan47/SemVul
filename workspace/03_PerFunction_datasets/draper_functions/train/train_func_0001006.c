remove_bus_watch (gpointer user_data)
{
  guint watch_id = GPOINTER_TO_INT(user_data);
  UNITY_WEBAPPS_NOTE(INTEREST, "REMOVING BUS WATCH FOR %d", watch_id);
  g_bus_unwatch_name (watch_id);
  return FALSE;
}
