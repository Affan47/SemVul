psoutputstring (GtkPlotPC *pc,
		GtkPSFont *psfont,
		GtkPSFont *latin_psfont,
		gint height,
		const GdkWChar *wstring,
		const gchar *addstring)
{
  const GdkWChar *p;
  GdkWChar wcs[2];
  gint curcode = 0, code;
  gchar begin[] = { 0, '(', '<' };
  gchar end[] = { 0, ')', '>' };
  GtkPSFont *fonts[3];
  FILE *out = GTK_PLOT_PS(pc)->psfile;
  gchar *mbs, *c;

  fonts[0] = NULL;
  fonts[1] = latin_psfont;
  fonts[2] = psfont;

  p = wstring;

  if (psfont->i18n_latinfamily) {
    while (*p) {
      code = (*p >= 0 && *p <= 0x7f) ? 1 : 2;
      if (curcode && curcode != code)
	fprintf(out, "%c %s\n", end[curcode], addstring);
      if (curcode != code) {
	pssetfont(pc, fonts[code], height);
	fputc(begin[code], out);
      }

      curcode = code;

      wcs[0] = *p++;
      wcs[1] = 0;
      c = mbs = gdk_wcstombs(wcs);

      if (code == 2) {
	while (*c)
	  fprintf(out, "%02x", (unsigned char)(*c++));
      } else {
	if (*c == '(' || *c == ')')
	  fputc('\\', out);
	fputc(*c, out);
      }

      g_free(mbs);
    }
  } else {
    c = mbs = gdk_wcstombs(wstring);

    while (*c) {
      if (curcode == 0) {
	pssetfont(pc, psfont, height);
	fputc(begin[1], out);
	curcode = 1;
      }

      if (*c == '(' || *c == ')')
	fputc('\\', out);
      fputc(*c++, out);
    }

    g_free(mbs);
  }

  if (curcode)
    fprintf(out, "%c %s\n", end[curcode], addstring);
}
