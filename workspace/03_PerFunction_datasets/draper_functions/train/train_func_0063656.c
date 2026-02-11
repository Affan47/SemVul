gngb_file_open(char *filename,char *mode,char type) {
  GNGB_FILE *f=(GNGB_FILE *)malloc(sizeof(GNGB_FILE));
  if (!f) return NULL;

  if (type!=UNKNOW_FILE_TYPE) f->type=type;
  else f->type=get_type_file(filename);

  switch(f->type) {
  case GZIP_FILE_TYPE:
#ifdef HAVE_LIBZ
    f->stream=(char *)gzopen(filename,mode);
#else
    fprintf(stderr,"Gzip file unsupported\n");
    return NULL;
#endif
    break;

  case ZIP_ARCH_FILE_TYPE:
#ifdef HAVE_LIBZ
    f->stream=(char *)unzOpen(filename);
#else
    fprintf(stderr,"Zip file unsupported\n");
    return NULL;
#endif
    break;

  case BZIP_FILE_TYPE:
#ifdef HAVE_LIBBZ2
    f->stream=(char *)BZ2_bzopen(filename,mode);
    break;
#else
    fprintf(stderr,"Bzip2 file unsupported\n");
    return NULL;
#endif
    break;

  case NORMAL_FILE_TYPE:
  case GB_ROM_FILE_TYPE:
    f->stream=(char *)fopen(filename,mode);
    break;
  default:
    return NULL;
  }

  if (!f->stream) {
    free(f);
    return NULL;
  }
  return f;
}
