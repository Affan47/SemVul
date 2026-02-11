bgav_pmt_section_dump(pmt_section_t * pmts)
  {
  int i;
  const stream_type_t * stream_type;

  bgav_dprintf( "PMT section:\n");
  bgav_dprintf( "  table_id:               %02x\n",   pmts->table_id);
  bgav_dprintf( "  section_length:         %d\n",     pmts->section_length);
  bgav_dprintf( "  program_number:         %d\n",     pmts->program_number);
  bgav_dprintf( "  current_next_indicator: %d\n",     pmts->current_next_indicator);
  bgav_dprintf( "  section_number:         %d\n",     pmts->section_number);
  bgav_dprintf( "  last_section_number:    %d\n",     pmts->last_section_number);
  bgav_dprintf( "  pcr_pid:                0x%04x (%d)\n",
                pmts->pcr_pid, pmts->pcr_pid);
  bgav_dprintf( "  descriptor:             ");
  if(pmts->descriptor_len)
    bgav_hexdump((uint8_t*)pmts->descriptor, pmts->descriptor_len, pmts->descriptor_len);
  else
    bgav_dprintf( "[none]\n");
  bgav_dprintf( "  Number of streams:      %d\n",     pmts->num_streams);

  for(i = 0; i < pmts->num_streams; i++)
    {
    stream_type = get_stream_type(pmts->streams[i].type);

    bgav_dprintf( "  Stream %d\n", i+1);

    if(stream_type)
      bgav_dprintf( "    type:       0x%02x (%s)\n",
                    pmts->streams[i].type, stream_type->description);
    else
      bgav_dprintf( "    type:       0x%02x (unknown)\n",
                    pmts->streams[i].type);

    bgav_dprintf( "    PID:        0x%04x (%d)\n",
                  pmts->streams[i].pid, pmts->streams[i].pid);
    bgav_dprintf( "    descriptor: ");

    if(pmts->streams[i].descriptor_len)
      bgav_hexdump((uint8_t*)pmts->streams[i].descriptor,
                   pmts->streams[i].descriptor_len,
                   pmts->streams[i].descriptor_len);
    else
      bgav_dprintf( "[none]\n");
    }
  }
