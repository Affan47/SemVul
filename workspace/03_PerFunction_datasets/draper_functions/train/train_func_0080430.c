Fax3VSetField(TIFF* tif, uint32 tag, va_list ap)
{
  Fax3BaseState* sp = Fax3State(tif);
  const TIFFField* fip;

  assert(sp != 0);
  assert(sp->vsetparent != 0);

  switch (tag) {
  case TIFFTAG_FAXMODE:
    sp->mode = (int) va_arg(ap, int);
    return 1;
  case TIFFTAG_FAXFILLFUNC:
    DecoderState(tif)->fill = va_arg(ap, TIFFFaxFillFunc);
    return 1;
  case TIFFTAG_GROUP3OPTIONS:

    if (tif->tif_dir.td_compression == COMPRESSION_CCITTFAX3)
      sp->groupoptions = (uint32) va_arg(ap, uint32);
    break;
  case TIFFTAG_GROUP4OPTIONS:

    if (tif->tif_dir.td_compression == COMPRESSION_CCITTFAX4)
      sp->groupoptions = (uint32) va_arg(ap, uint32);
    break;
  case TIFFTAG_BADFAXLINES:
    sp->badfaxlines = (uint32) va_arg(ap, uint32);
    break;
  case TIFFTAG_CLEANFAXDATA:
    sp->cleanfaxdata = (uint16) va_arg(ap, uint16_vap);
    break;
  case TIFFTAG_CONSECUTIVEBADFAXLINES:
    sp->badfaxrun = (uint32) va_arg(ap, uint32);
    break;
  default:
    return (*sp->vsetparent)(tif, tag, ap);
  }

  if ((fip = TIFFFieldWithTag(tif, tag)))
    TIFFSetFieldBit(tif, fip->field_bit);
  else
    return 0;

  tif->tif_flags |= TIFF_DIRTYDIRECT;
  return 1;
}
