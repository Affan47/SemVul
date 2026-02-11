qtdemux_dump_cmvd (GstQTDemux * qtdemux, GstByteReader * data, int depth)
{
  if (!qt_atom_parser_has_remaining (data, 4))
    return FALSE;

  GST_LOG ("%*s  length: %d", depth, "", GET_UINT32 (data));
  return TRUE;
}
