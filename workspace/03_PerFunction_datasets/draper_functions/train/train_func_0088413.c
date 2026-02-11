print_plugin_info (GstPlugin * plugin)
{
  n_print ("Plugin Details:\n");
  n_print ("  Name:\t\t\t%s\n", plugin->desc.name);
  n_print ("  Description:\t\t%s\n", plugin->desc.description);
  n_print ("  Filename:\t\t%s\n",
      plugin->filename ? plugin->filename : "(null)");
  n_print ("  Version:\t\t%s\n", plugin->desc.version);
  n_print ("  License:\t\t%s\n", plugin->desc.license);
  n_print ("  Source module:\t%s\n", plugin->desc.source);
  if (plugin->desc.release_datetime != NULL) {
    const gchar *tz = "(UTC)";
    gchar *str, *sep;


    str = g_strdup (plugin->desc.release_datetime);
    sep = strstr (str, "T");
    if (sep != NULL) {
      *sep = ' ';
      sep = strstr (sep + 1, "Z");
      if (sep != NULL)
        *sep = ' ';
    } else {
      tz = "";
    }
    n_print ("  Source release date:\t%s%s\n", str, tz);
    g_free (str);
  }
  n_print ("  Binary package:\t%s\n", plugin->desc.package);
  n_print ("  Origin URL:\t\t%s\n", plugin->desc.origin);
  n_print ("\n");
}
