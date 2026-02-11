gnac_properties_dup_bitrate(const GValue *value)
{
  guint val = g_value_get_uint(value);
  if (val == 0) return NULL;

  val = gnac_utils_convert_bps_to_kbps(val);

  if (libgnac_metadata_tag_exists(tags, GNAC_TAG_VBR)) {

    return  g_strdup_printf(_("~%d kbps (VBR)"), val);
  } else {

    return g_strdup_printf(_("%d kbps"), val);
  }
}
