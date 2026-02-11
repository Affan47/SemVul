clutter_animation_has_signal_prefix (const gchar *property_name,
                                     GConnectFlags *flags,
                                     int *offset)
{
  int i;

  if (!g_str_has_prefix (property_name, "signal"))
    return FALSE;

  for (i = 0; i < G_N_ELEMENTS (signal_prefixes); i++)
    if (g_str_has_prefix (property_name + 6, signal_prefixes[i].name))
      {
        *offset = strlen (signal_prefixes[i].name) + 6;
        *flags = signal_prefixes[i].flags;
        return TRUE;
      }

  return FALSE;
}
