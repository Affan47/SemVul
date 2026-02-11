cups_raster_update(cups_raster_t *r)
{
  if (r->sync == CUPS_RASTER_SYNCv1 || r->sync == CUPS_RASTER_REVSYNCv1 ||
      r->header.cupsNumColors == 0)
  {


    switch (r->header.cupsColorSpace)
    {
      case CUPS_CSPACE_W :
      case CUPS_CSPACE_K :
      case CUPS_CSPACE_WHITE :
      case CUPS_CSPACE_GOLD :
      case CUPS_CSPACE_SILVER :
      case CUPS_CSPACE_SW :
          r->header.cupsNumColors = 1;
	  break;

      case CUPS_CSPACE_RGB :
      case CUPS_CSPACE_CMY :
      case CUPS_CSPACE_YMC :
      case CUPS_CSPACE_CIEXYZ :
      case CUPS_CSPACE_CIELab :
      case CUPS_CSPACE_SRGB :
      case CUPS_CSPACE_ADOBERGB :
      case CUPS_CSPACE_ICC1 :
      case CUPS_CSPACE_ICC2 :
      case CUPS_CSPACE_ICC3 :
      case CUPS_CSPACE_ICC4 :
      case CUPS_CSPACE_ICC5 :
      case CUPS_CSPACE_ICC6 :
      case CUPS_CSPACE_ICC7 :
      case CUPS_CSPACE_ICC8 :
      case CUPS_CSPACE_ICC9 :
      case CUPS_CSPACE_ICCA :
      case CUPS_CSPACE_ICCB :
      case CUPS_CSPACE_ICCC :
      case CUPS_CSPACE_ICCD :
      case CUPS_CSPACE_ICCE :
      case CUPS_CSPACE_ICCF :
          r->header.cupsNumColors = 3;
	  break;

      case CUPS_CSPACE_RGBA :
      case CUPS_CSPACE_RGBW :
      case CUPS_CSPACE_CMYK :
      case CUPS_CSPACE_YMCK :
      case CUPS_CSPACE_KCMY :
      case CUPS_CSPACE_GMCK :
      case CUPS_CSPACE_GMCS :
          r->header.cupsNumColors = 4;
	  break;

      case CUPS_CSPACE_KCMYcm :
          if (r->header.cupsBitsPerPixel < 8)
            r->header.cupsNumColors = 6;
	  else
            r->header.cupsNumColors = 4;
	  break;

      case CUPS_CSPACE_DEVICE1 :
      case CUPS_CSPACE_DEVICE2 :
      case CUPS_CSPACE_DEVICE3 :
      case CUPS_CSPACE_DEVICE4 :
      case CUPS_CSPACE_DEVICE5 :
      case CUPS_CSPACE_DEVICE6 :
      case CUPS_CSPACE_DEVICE7 :
      case CUPS_CSPACE_DEVICE8 :
      case CUPS_CSPACE_DEVICE9 :
      case CUPS_CSPACE_DEVICEA :
      case CUPS_CSPACE_DEVICEB :
      case CUPS_CSPACE_DEVICEC :
      case CUPS_CSPACE_DEVICED :
      case CUPS_CSPACE_DEVICEE :
      case CUPS_CSPACE_DEVICEF :
          r->header.cupsNumColors = r->header.cupsColorSpace -
	                            CUPS_CSPACE_DEVICE1 + 1;
	  break;
    }
  }


  if (r->header.cupsColorOrder == CUPS_ORDER_CHUNKED)
    r->bpp = (r->header.cupsBitsPerPixel + 7) / 8;
  else
    r->bpp = (r->header.cupsBitsPerColor + 7) / 8;


  if (r->header.cupsColorOrder == CUPS_ORDER_PLANAR)
    r->remaining = r->header.cupsHeight * r->header.cupsNumColors;
  else
    r->remaining = r->header.cupsHeight;


  if (r->compressed)
  {
    if (r->pixels != NULL)
      free(r->pixels);

    r->pixels   = calloc(r->header.cupsBytesPerLine, 1);
    r->pcurrent = r->pixels;
    r->pend     = r->pixels + r->header.cupsBytesPerLine;
    r->count    = 0;
  }
}
