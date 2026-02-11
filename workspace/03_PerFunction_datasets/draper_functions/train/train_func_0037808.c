add_new_days_to_cache (LogviewLog *log, const char **new_lines, guint lines_offset)
{
  GSList *new_days, *l, *last_cached;
  int res;
  Day *day, *last;

  new_days = log_read_dates (new_lines, log->priv->file_time);


  last_cached = g_slist_last (log->priv->days);

  if (!last_cached) {

    log->priv->days = logview_utils_day_list_copy (new_days);
    return new_days;
  }

  for (l = new_days; l; l = l->next) {
    res = days_compare (l->data, last_cached->data);
    day = l->data;

    if (res > 0) {


      day->first_line += lines_offset;
      day->last_line += lines_offset;
      log->priv->days = g_slist_append (log->priv->days, logview_utils_day_copy (day));
    } else if (res == 0) {
      last = last_cached->data;


      last->last_line += day->last_line;
    }
  }

  return new_days;
}
