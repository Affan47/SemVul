gst_tag_get_license_nick (const gchar * license_ref)
{
  GstTagLicenseFlags flags;
  const gchar *creator_prefix, *res;
  gchar *nick, *c;

  g_return_val_if_fail (license_ref != NULL, NULL);

  flags = gst_tag_get_license_flags (license_ref);

  if ((flags & GST_TAG_LICENSE_CREATIVE_COMMONS_LICENSE)) {
    creator_prefix = "CC ";
  } else if ((flags & GST_TAG_LICENSE_FREE_SOFTWARE_FOUNDATION_LICENSE)) {
    creator_prefix = "FSF ";
  } else if (g_str_has_suffix (license_ref, "publicdomain/")) {
    creator_prefix = "";
  } else {
    return NULL;
  }

  nick = g_strdup_printf ("%s%s", creator_prefix,
      license_ref + sizeof (CC_LICENSE_REF_PREFIX) - 1);
  g_strdelimit (nick, "/", ' ');
  g_strchomp (nick);
  for (c = nick; *c != '\0'; ++c)
    *c = g_ascii_toupper (*c);

  GST_LOG ("%s => nick %s", license_ref, nick);
  res = g_intern_string (nick);
  g_free (nick);

  return res;
}
