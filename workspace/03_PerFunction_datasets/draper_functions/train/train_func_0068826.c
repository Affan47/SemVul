attr_format_assessment (gint     current,
                        gint     worst,
                        gint     threshold,
                        guint16  flags)
{
  gchar *ret;
  gboolean failed = FALSE;
  gboolean failed_in_the_past = FALSE;

  if (current > 0 && threshold > 0 && current <= threshold)
    failed = TRUE;

  if (worst > 0 && threshold > 0 && worst <= threshold)
    failed_in_the_past = TRUE;

  if (failed)
    {


      ret = g_strdup_printf ("<span foreground=\"#ff0000\"><b>%s</b></span>",

                             _("FAILING"));
    }
  else if (failed_in_the_past)
    {


      ret = g_strdup_printf ("<span foreground=\"#ff0000\">%s</span>",

                             _("Failed in the past"));
    }
  else
    {
      ret = g_strdup (_("OK"));
    }

  return ret;
}
