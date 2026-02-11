is_valid_color_balance_element (GstColorBalance * bal)
{
  gboolean have_brightness = FALSE;
  gboolean have_contrast = FALSE;
  gboolean have_hue = FALSE;
  gboolean have_saturation = FALSE;
  const GList *channels, *l;

  channels = gst_color_balance_list_channels (bal);
  for (l = channels; l; l = l->next) {
    GstColorBalanceChannel *ch = l->data;

    if (g_strrstr (ch->label, "BRIGHTNESS"))
      have_brightness = TRUE;
    else if (g_strrstr (ch->label, "CONTRAST"))
      have_contrast = TRUE;
    else if (g_strrstr (ch->label, "HUE"))
      have_hue = TRUE;
    else if (g_strrstr (ch->label, "SATURATION"))
      have_saturation = TRUE;
  }

  return have_brightness && have_contrast && have_hue && have_saturation;
}
