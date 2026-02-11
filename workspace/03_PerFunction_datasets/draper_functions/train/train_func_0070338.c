exif_examine_app(exif_app_t* app)
{
  gbuint16 endianess;
  gbuint32 ident;
  gbfile* ftmp = exif_app->fcache;
  int i;

  gbfrewind(ftmp);
  ident = gbfgetuint32(ftmp);
  is_fatal(ident != 0x66697845, MYNAME ": Invalid EXIF header magic.");
  is_fatal(gbfgetint16(ftmp) != 0, MYNAME ": Error in EXIF header.");
  endianess = gbfgetint16(ftmp);

#ifdef EXIF_DBG
  printf(MYNAME ": endianess = 0x%04X\n", endianess);
#endif
  if (endianess == 0x4949) {
    ftmp->big_endian = 0;
  } else if (endianess == 0x4D4D) {
    ftmp->big_endian = 1;
  } else {
    fatal(MYNAME ": Invalid endianess identifier 0x%04X!\n", endianess);
  }

  gbfseek(ftmp, 6, SEEK_SET);
  app->fexif = gbfopen(NULL, "wb", MYNAME);
  app->fexif->big_endian = ftmp->big_endian;
  i = gbfcopyfrom(app->fexif, ftmp, 0x7FFFFFFF);

  exif_read_app(exif_app);
}
