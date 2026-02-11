gst_vcd_parse_get_in_offset (gint64 out_offset)
{
  gint64 in_offset, chunknum, rest;

  if (out_offset == -1)
    return -1;

  if (G_UNLIKELY (out_offset < -1)) {
    GST_WARNING ("unexpected/invalid out_offset %" G_GINT64_FORMAT, out_offset);
    return out_offset;
  }

  chunknum = out_offset / GST_CDXA_DATA_SIZE;
  rest = out_offset % GST_CDXA_DATA_SIZE;

  in_offset = chunknum * GST_CDXA_SECTOR_SIZE;
  if (rest > 0)
    in_offset += GST_CDXA_HEADER_SIZE + rest;

  GST_LOG ("transformed out_offset %" G_GINT64_FORMAT " to in_offset %"
      G_GINT64_FORMAT, out_offset, in_offset);

  return in_offset;
}
