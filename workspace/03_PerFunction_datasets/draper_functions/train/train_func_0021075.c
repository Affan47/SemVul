bgav_qt_moov_read(qt_atom_header_t * h, bgav_input_context_t * input,
                      qt_moov_t * ret)
  {
  qt_atom_header_t ch;
  memcpy(&ret->h, h, sizeof(*h));

  while(input->position < h->start_position + h->size)
    {
    if(!bgav_qt_atom_read_header(input, &ch))
      return 0;
    switch(ch.fourcc)
      {
      case BGAV_MK_FOURCC('c', 'm', 'o', 'v'):

        return bgav_qt_cmov_read(&ch, input, ret);
        break;

      case BGAV_MK_FOURCC('r', 'm', 'r', 'a'):
        if(!bgav_qt_rmra_read(&ch, input, &ret->rmra))
          return 0;
        ret->has_rmra = 1;
        break;
      case BGAV_MK_FOURCC('t', 'r', 'a', 'k'):
        ret->num_tracks++;
        ret->tracks =
          realloc(ret->tracks, sizeof(*(ret->tracks))*ret->num_tracks);
        memset(&ret->tracks[ret->num_tracks-1], 0,
               sizeof(*ret->tracks));
        if(!bgav_qt_trak_read(&ch, input, &ret->tracks[ret->num_tracks-1]))
          return 0;

        break;
      case BGAV_MK_FOURCC('m', 'v', 'h', 'd'):
        if(!bgav_qt_mvhd_read(&ch, input, &ret->mvhd))
          return 0;
        break;
      case BGAV_MK_FOURCC('u', 'd', 't', 'a'):
        if(!bgav_qt_udta_read(&ch, input, &ret->udta))
          return 0;
        ret->has_udta = 1;
        break;
      default:
        bgav_qt_atom_skip_unknown(input, &ch, h->fourcc);
        break;
      }
    }


  return 1;
  }
