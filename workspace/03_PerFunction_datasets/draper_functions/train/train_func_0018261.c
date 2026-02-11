vt_env_metrics_sep()
{
  static char* metrics_sep = NULL;
  char* tmp;

  if (!metrics_sep)
    {
      tmp = getenv("VT_METRICS_SEP");
      if (tmp && strlen(tmp) > 0)
        {
          vt_cntl_msg(2, "VT_METRICS_SEP=%s", tmp);

          metrics_sep = tmp;
        }
      else
        {
          metrics_sep = ":";
        }
    }
  return metrics_sep;
}
