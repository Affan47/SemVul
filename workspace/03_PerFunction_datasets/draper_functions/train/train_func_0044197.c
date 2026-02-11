gst_avi_demux_parse_subindex (GstAviDemux * avi, GstAviStream * stream,
    GstBuffer * buf)
{
  guint8 *data;
  guint16 bpe;
  guint32 num, i;
  guint64 baseoff;
  guint size;

  if (!buf)
    return TRUE;

  size = GST_BUFFER_SIZE (buf);


  if (size < 24)
    goto too_small;

  data = GST_BUFFER_DATA (buf);


  if (data[3] & 0x80)
    goto not_implemented;


  bpe = (data[2] & 0x01) ? 12 : 8;
  if (GST_READ_UINT16_LE (data) != bpe / 4 ||
      (data[2] & 0xfe) != 0x0 || data[3] != 0x1) {
    GST_WARNING_OBJECT (avi,
        "Superindex for stream %d has unexpected "
        "size_entry %d (bytes) or flags 0x%02x/0x%02x",
        stream->num, GST_READ_UINT16_LE (data), data[2], data[3]);
    bpe = GST_READ_UINT16_LE (data) * 4;
  }
  num = GST_READ_UINT32_LE (&data[4]);
  baseoff = GST_READ_UINT64_LE (&data[12]);


  if (num == 0)
    goto empty_index;

  GST_INFO_OBJECT (avi, "Parsing subindex, nr_entries = %6d", num);

  for (i = 0; i < num; i++) {
    GstAviIndexEntry entry;

    if (size < 24 + bpe * (i + 1))
      break;


    entry.offset = baseoff + GST_READ_UINT32_LE (&data[24 + bpe * i]);
    entry.size = GST_READ_UINT32_LE (&data[24 + bpe * i + 4]);

    if (stream->strh->type == GST_RIFF_FCC_auds) {

      ENTRY_SET_KEYFRAME (&entry);
    } else {

      entry.flags = (entry.size & 0x80000000) ? 0 : GST_AVI_KEYFRAME;
    }
    entry.size &= ~0x80000000;


    if (G_UNLIKELY (!gst_avi_demux_add_index (avi, stream, num, &entry)))
      goto out_of_mem;
  }
  gst_buffer_unref (buf);

  return TRUE;


too_small:
  {
    GST_ERROR_OBJECT (avi,
        "Not enough data to parse subindex (%d available, 24 needed)", size);
    gst_buffer_unref (buf);
    return TRUE;
  }
not_implemented:
  {
    GST_ELEMENT_ERROR (avi, STREAM, NOT_IMPLEMENTED, (NULL),
        ("Subindex-is-data is not implemented"));
    gst_buffer_unref (buf);
    return FALSE;
  }
empty_index:
  {
    GST_DEBUG_OBJECT (avi, "the index is empty");
    gst_buffer_unref (buf);
    return TRUE;
  }
out_of_mem:
  {
    GST_ELEMENT_ERROR (avi, RESOURCE, NO_SPACE_LEFT, (NULL),
        ("Cannot allocate memory for %u*%u=%u bytes",
            (guint) sizeof (GstAviIndexEntry), num,
            (guint) sizeof (GstAviIndexEntry) * num));
    gst_buffer_unref (buf);
    return FALSE;
  }
}
