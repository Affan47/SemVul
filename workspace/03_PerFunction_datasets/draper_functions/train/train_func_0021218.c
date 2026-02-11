bgav_qt_mdia_read(qt_atom_header_t * h, bgav_input_context_t * input,
                      qt_mdia_t * ret)
  {
  qt_atom_header_t ch;
  memcpy(&ret->h, h, sizeof(*h));

  while(input->position < h->start_position + h->size)
    {
    if(!bgav_qt_atom_read_header(input, &ch))
      return 0;
    switch(ch.fourcc)
      {
      case BGAV_MK_FOURCC('m', 'd', 'h', 'd'):
        if(!bgav_qt_mdhd_read(&ch, input, &ret->mdhd))
          return 0;
        break;
      case BGAV_MK_FOURCC('h', 'd', 'l', 'r'):
        if(!bgav_qt_hdlr_read(&ch, input, &ret->hdlr))
          return 0;
        break;
      case BGAV_MK_FOURCC('m', 'i', 'n', 'f'):
        if(!bgav_qt_minf_read(&ch, input, &ret->minf))
          return 0;
        break;
      default:
        bgav_qt_atom_skip_unknown(input, &ch, h->fourcc);
        break;

      }
    }
  return 1;
  }
