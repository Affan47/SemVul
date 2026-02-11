bgav_qt_trak_read(qt_atom_header_t * h, bgav_input_context_t * input,
                      qt_trak_t * ret)
  {
  qt_atom_header_t ch;
  memcpy(&ret->h, h, sizeof(*h));
  while(input->position < h->start_position + h->size)
    {
    if(!bgav_qt_atom_read_header(input, &ch))
      return 0;
    switch(ch.fourcc)
      {
      case BGAV_MK_FOURCC('m', 'd', 'i', 'a'):
        if(!bgav_qt_mdia_read(&ch, input, &ret->mdia))
          return 0;
        break;
      case BGAV_MK_FOURCC('t', 'k', 'h', 'd'):
        if(!bgav_qt_tkhd_read(&ch, input, &ret->tkhd))
          return 0;
        break;
      case BGAV_MK_FOURCC('u', 'd', 't', 'a'):
        if(!bgav_qt_udta_read(&ch, input, &ret->udta))
          return 0;
        ret->has_udta = 1;
        break;
      case BGAV_MK_FOURCC('e', 'd', 't', 's'):
        if(!bgav_qt_edts_read(&ch, input, &ret->edts))
          return 0;
        ret->has_edts = 1;
        break;
      case BGAV_MK_FOURCC('t', 'r', 'e', 'f'):
        if(!bgav_qt_tref_read(&ch, input, &ret->tref))
          return 0;
        ret->has_tref = 1;
        break;
      default:
        bgav_qt_atom_skip_unknown(input, &ch,h->fourcc);
        break;
      }
    }

  bgav_qt_stsd_finalize(&ret->mdia.minf.stbl.stsd, ret, input->opt);

  return 1;
  }
