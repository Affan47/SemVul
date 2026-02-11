MagickToMime(const char *magick)
{
  typedef struct _MediaType
  {
    const char
      *magick,
      *media;
  } MediaType;

  char
    media[MaxTextExtent];

  MediaType
    *entry;

  static MediaType
    MediaTypes[] =
    {
      { "avi",   "video/avi" },
      { "cgm",   "image/cgm;Version=4;ProfileId=WebCGM" },
      { "dcm",   "application/dicom" },
      { "epdf",  "application/pdf" },
      { "epi",   "application/postscript" },
      { "eps",   "application/postscript" },
      { "eps2",  "application/postscript" },
      { "eps3",  "application/postscript" },
      { "epsf",  "application/postscript" },
      { "ept",   "application/postscript" },
      { "fax",   "image/g3fax" },
      { "fpx",   "image/vnd.fpx" },
      { "g3",    "image/g3fax" },
      { "gif",   "image/gif" },
      { "gif87", "image/gif" },
      { "jpeg",  "image/jpeg" },
      { "mng",   "video/x-mng" },
      { "mpeg",  "video/mpeg" },
      { "png",   "image/png" },
      { "pdf",   "application/pdf" },
      { "ps",    "application/postscript" },
      { "ps2",   "application/postscript" },
      { "ps3",   "application/postscript" },
      { "svg",   "image/svg+xml" },
      { "tif",   "image/tiff" },
      { "tiff",  "image/tiff" },
      { "wbmp",  "image/vnd.wap.wbmp" },
      { (char *) NULL, (char *) NULL }
    };

  for (entry=MediaTypes; entry->magick != (char *) NULL; entry++)
    if (LocaleCompare(entry->magick,magick) == 0)
      return(AllocateString(entry->media));
  FormatString(media,"image/x-%.1024s",magick);
  LocaleLower(media+8);
  return(AllocateString(media));
}
