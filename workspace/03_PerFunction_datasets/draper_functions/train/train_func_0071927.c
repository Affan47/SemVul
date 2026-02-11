dump_frame(bgav_id3v2_frame_t * frame)
  {
  int i;
  bgav_dprintf( "Header:\n");
  bgav_dprintf( "  Fourcc: ");
  bgav_dump_fourcc(frame->header.fourcc);
  bgav_dprintf( "\n");

  bgav_dprintf( "  Size:   %d\n", frame->header.size);

  bgav_dprintf( "  Flags:  ");

  if(frame->header.flags & ID3V2_FRAME_TAG_ALTER_PRESERVATION)
    bgav_dprintf( "ALTER_PRESERVATION ");
  if(frame->header.flags & ID3V2_FRAME_READ_ONLY)
    bgav_dprintf( "READ_ONLY ");
  if(frame->header.flags & ID3V2_FRAME_GROUPING)
    bgav_dprintf( "GOUPING ");
  if(frame->header.flags & ID3V2_FRAME_COMPRESSION)
    bgav_dprintf( "COMPRESSION ");
  if(frame->header.flags & ID3V2_FRAME_ENCRYPTION)
    bgav_dprintf( "ENCRYPTION ");
  if(frame->header.flags & ID3V2_FRAME_UNSYNCHRONIZED)
    bgav_dprintf( "UNSYNCHRONIZED ");
  if(frame->header.flags & ID3V2_FRAME_DATA_LENGTH)
    bgav_dprintf( "DATA_LENGTH");

  bgav_dprintf( "\n");

  if(frame->data)
    {
    bgav_dprintf( "Raw data:\n");
    bgav_hexdump(frame->data, frame->header.size, 16);
    }
  else if(frame->strings)
    {
    bgav_dprintf( "Strings:\n");
    i = 0;
    while(frame->strings[i])
      {
      bgav_dprintf( "%02x: %s\n", i, frame->strings[i]);
      i++;
      }
    }
  }
