has_xing_header (guint32 header, guchar * data, gsize size)
{
  data += 4;
  data += get_xing_offset (header);

  if (memcmp (data, "Xing", 4) == 0 ||
      memcmp (data, "Info", 4) == 0 || memcmp (data, "VBRI", 4) == 0)
    return TRUE;
  else
    return FALSE;
}
