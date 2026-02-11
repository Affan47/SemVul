xhtml_barchart(FILE *outf, Outchoices *od, int y, char graphby) {
  int i, j;
  logical first = TRUE;

  fprintf(outf, "<td class=\"%sbar\">", od->cssprefix);

  if (ISLOWER(graphby)) {
    for (i = 0; i < y; i++)
      xhtml_putch(outf, od->markchar);
  }
  else {
    for (j = 32; j >= 1; j /= 2) {
      while (y >= j) {
	fputs("<img src=\"", outf);
	xhtmlputs(outf, od, od->imagedir, IN_HREF);
	fprintf(outf, "bar%c%d.%s\" alt=\"", od->barstyle, j,
		od->pngimages?"png":"gif");
	if (first) {
	  for (i = 0; i < y; i++)
	    xhtml_putch(outf, od->markchar);
	  first = FALSE;
	}
	fputs("\" />", outf);
	y -= j;
      }
    }
  }

  fputs("</td>", outf);
}
