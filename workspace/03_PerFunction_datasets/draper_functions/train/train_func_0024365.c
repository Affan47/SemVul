read_timecode_component(bgav_input_context_t * input,
                                   partition_t * ret, mxf_metadata_t * m,
                                   int tag, int size, uint8_t * uid)
  {
  mxf_timecode_component_t * s = (mxf_timecode_component_t *)m;
  switch(tag)
    {
    case 0x0201:
      if(bgav_input_read_data(input, s->data_definition_ul, 16) < 16)
        return 0;
      break;
    case 0x0202:
      if(!bgav_input_read_64_be(input, &s->duration))
        return 0;
      break;
    case 0x1502:
      if(!bgav_input_read_16_be(input, &s->rounded_timecode_base))
        return 0;
      break;
    case 0x1501:
      if(!bgav_input_read_64_be(input, &s->start_timecode))
        return 0;
      break;
    case 0x1503:
      if(!bgav_input_read_8(input, &s->drop_frame))
        return 0;
      break;
    default:
#ifdef DUMP_UNKNOWN
     bgav_dprintf("Unknown local tag in timecode component: %04x, %d bytes\n", tag, size);
     if(size)
       bgav_input_skip_dump(input, size);
#endif
     break;
    }
  return 1;
  }
