__exif_tag_capturing_gain_adjustment_to_exif_value (const gchar * str)
{
  if (str == NULL)
    goto end;

  if (strcmp (str, "none") == 0)
    return 0;
  else if (strcmp (str, "low-gain-up") == 0)
    return 1;
  else if (strcmp (str, "high-gain-up") == 0)
    return 2;
  else if (strcmp (str, "low-gain-down") == 0)
    return 3;
  else if (strcmp (str, "high-gain-down") == 0)
    return 4;

end:
  GST_WARNING ("Invalid capturing gain adjustment type: %s", str);
  return -1;
}
