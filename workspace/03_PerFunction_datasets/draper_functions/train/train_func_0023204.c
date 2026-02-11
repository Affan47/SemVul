format_image(uint8_t **out, int render_fmt, int misc_int, VInfo *ji, uint8_t *buf) {
#ifdef __USE_XOPEN2K8
  size_t rs = 0;
  FILE *x = open_memstream((char**) out, &rs);
#elif defined HAVE_WINDOWS
  char tfn[L_tmpnam];
  tmpnam(tfn);
  FILE *x = fopen(tfn, "w+b");
#else
  FILE *x = tmpfile();
#endif
  if (!x) {
    dlog(LOG_ERR, "IMF: tmpfile() creation failed.\n");
    return(0);
  }

  switch (render_fmt) {
    case 1:
      {
        if (misc_int < 5 || misc_int > 100)
          misc_int = JPEG_QUALITY;
      if (write_jpeg(ji, buf, misc_int, x))
        dlog(LOG_ERR, "IMF: Could not write jpeg\n");
      break;
      }
    case 2:
      if (write_png(ji, buf, x))
        dlog(LOG_ERR, "IMF: Could not write png\n");
      break;
    case 3:
      if (write_ppm(ji, buf, x))
        dlog(LOG_ERR, "IMF: Could not write ppm\n");
      break;
    default:
        dlog(LOG_ERR, "IMF: Unknown outformat %d\n", render_fmt);
        fclose(x);
        return 0;
      break;
  }
#ifdef __USE_XOPEN2K8
  fclose(x);
  return rs;
#elif defined HAVE_WINDOWS
  fclose(x);
  x = fopen(tfn, "rb");
#else
  fflush(x);
#endif

  fseek (x , 0 , SEEK_END);
  long int rsize = ftell (x);
  rewind(x);
  if (fseek(x, 0L, SEEK_SET) < 0) {
    dlog(LOG_WARNING, "IMF: fseek failed\n");
  }
  fflush(x);
  *out = (uint8_t*) malloc(rsize*sizeof(uint8_t));
  if (fread(*out, sizeof(char), rsize, x) != rsize) {
    dlog(LOG_WARNING, "IMF: short read. - possibly incomplete image\n");
  }
  fclose(x);
#ifdef HAVE_WINDOWS
  unlink(tfn);
#endif
  return (rsize);
}
