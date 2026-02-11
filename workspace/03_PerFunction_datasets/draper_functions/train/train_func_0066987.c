write_stream(const char *output_name, Gif_Stream *gfs)
{
  FILE *f;

  if (output_name)
    f = fopen(output_name, "wb");
  else {
#ifndef OUTPUT_GIF_TO_TERMINAL
    extern int isatty(int);
    if (isatty(fileno(stdout))) {
      error(0, "<stdout>: is a terminal");
      return;
    }
#endif
#if defined(_MSDOS) || defined(_WIN32)
    _setmode(_fileno(stdout), _O_BINARY);
#elif defined(__DJGPP__)
    setmode(fileno(stdout), O_BINARY);
#elif defined(__EMX__)
    _fsetmode(stdout, "b");
#endif
    f = stdout;
    output_name = "<stdout>";
  }

  if (f) {
    Gif_FullWriteFile(gfs, &gif_write_info, f);
    fclose(f);
    any_output_successful = 1;
  } else
    error(0, "%s: %s", output_name, strerror(errno));
}
