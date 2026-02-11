find_psc (GstByteReader * br)
{
  guint psc_pos = -1, psc;

  if (!gst_byte_reader_peek_uint24_be (br, &psc))
    goto failed;


  while ((gst_byte_reader_get_remaining (br) >= 3)) {
    if (gst_byte_reader_peek_uint24_be (br, &psc) &&
        ((psc & 0xfffffc) == 0x000080)) {
      psc_pos = gst_byte_reader_get_pos (br);
      break;
    } else
      gst_byte_reader_skip (br, 1);
  }

failed:

  return psc_pos;
}
