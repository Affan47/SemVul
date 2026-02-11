bgav_qt_minf_read(qt_atom_header_t * h, bgav_input_context_t * input,
                      qt_minf_t * ret)
  {
  qt_atom_header_t ch;
  memcpy(&ret->h, h, sizeof(*h));

  while(input->position < h->start_position + h->size)
    {
    if(!bgav_qt_atom_read_header(input, &ch))
      return 0;
    switch(ch.fourcc)
      {
      case BGAV_MK_FOURCC('h', 'd', 'l', 'r'):
        if(!bgav_qt_hdlr_read(&ch, input, &ret->hdlr))
          return 0;
        break;
      case BGAV_MK_FOURCC('d', 'i', 'n', 'f'):
        if(!bgav_qt_dinf_read(&ch, input, &ret->dinf))
          return 0;
        ret->has_dinf = 1;
        break;
      case BGAV_MK_FOURCC('g', 'm', 'h', 'd'):
        if(!bgav_qt_gmhd_read(&ch, input, &ret->gmhd))
          return 0;
        ret->has_gmhd = 1;
        break;
      case BGAV_MK_FOURCC('n', 'm', 'h', 'd'):
        if(!bgav_qt_nmhd_read(&ch, input, &ret->nmhd))
          return 0;
        ret->has_nmhd = 1;
        break;
      case BGAV_MK_FOURCC('s', 't', 'b', 'l'):
        if(!bgav_qt_stbl_read(&ch, input, &ret->stbl, ret))
          return 0;
        break;
      case BGAV_MK_FOURCC('v', 'm', 'h', 'd'):
        ret->has_vmhd = 1;
        bgav_qt_atom_skip(input, &ch);
        break;
      case BGAV_MK_FOURCC('s', 'm', 'h', 'd'):
        ret->has_smhd = 1;
        bgav_qt_atom_skip(input, &ch);
        break;
      default:
        bgav_qt_atom_skip_unknown(input, &ch, h->fourcc);
      }
    }
  return 1;
  }
