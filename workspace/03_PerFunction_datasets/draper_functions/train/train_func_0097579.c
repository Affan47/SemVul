ps_check(const char *name,
         uchar      *header,
	 int)
{
  const char	*home;
  char		preview[FL_PATH_MAX],
		outname[FL_PATH_MAX],
		command[FL_PATH_MAX];
  FILE		*in,
		*out;
  int		page;
  char		line[256];


  if (memcmp(header, "%!", 2) != 0)
    return 0;

  home = getenv("HOME");
  sprintf(preview, "%s/.preview.ppm", home ? home : "");

  if (memcmp(header, "%!PS", 4) == 0) {

    sprintf(outname, "%s/.preview.ps", home ? home : "");

    if (strcmp(name, outname) != 0) {
      in   = fl_fopen(name, "rb");
      out  = fl_fopen(outname, "wb");
      page = 0;

      while (fgets(line, sizeof(line), in) != NULL) {
	if (strncmp(line, "%%Page:", 7) == 0) {
          page ++;
	  if (page > 1) break;
	}

	fputs(line, out);
      }

      fclose(in);
      fclose(out);
    }
  } else {

    strncpy(outname, name, sizeof(outname) - 1);
    outname[sizeof(outname) - 1] = '\0';
  }

  sprintf(command,
          "gs -r100 -dFIXED -sDEVICE=ppmraw -dQUIET -dNOPAUSE -dBATCH "
	  "-sstdout=\"%%stderr\" -sOUTPUTFILE=\'%s\' \'%s\' 2>/dev/null",
	  preview, outname);

  if (system(command)) return 0;

  return new Fl_PNM_Image(preview);
}
