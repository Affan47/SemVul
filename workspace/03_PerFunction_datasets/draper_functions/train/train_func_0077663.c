cc_timezone_map_set_timezone (CcTimezoneMap *map,
                              const gchar   *timezone)
{
  GPtrArray *locations;
  guint i;
  char *real_tz;
  gboolean ret;

  real_tz = tz_info_get_clean_name (map->priv->tzdb, timezone);

  locations = tz_get_locations (map->priv->tzdb);
  ret = FALSE;

  for (i = 0; i < locations->len; i++)
    {
      TzLocation *loc = locations->pdata[i];

      if (!g_strcmp0 (loc->zone, real_tz ? real_tz : timezone))
        {
          set_location (map, loc);
          ret = TRUE;
          break;
        }
    }

  if (ret)
    gtk_widget_queue_draw (GTK_WIDGET (map));

  g_free (real_tz);

  return ret;
}
