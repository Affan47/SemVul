hex_html(FILE *fp, unsigned char *buf, unsigned len, unsigned ncolumns)
{
  unsigned int ui;

  fprintf(fp, "<tt>");
  for (ui = 0; ui < len; ui++) {
	fprintf(fp, "%02X", buf[ui] & 0xff);
	if ((ui + 1) % ncolumns == 0)
	  fprintf(fp, "<br>");
	else
	  fprintf(fp, " ");
  }
  fprintf(fp, "</tt>");
  fprintf(fp, "<p>len=%d<p>\n", len);
}
