line_out(const struct jbg85_dec_state *s,
	     unsigned char *start, size_t len, unsigned long y, void *file)
{
  if (y == 0) {

    fprintf((FILE *) file, "P4\n");
    fprintf((FILE *) file, "%10lu\n", jbg85_dec_getwidth(s));

    y_0 = jbg85_dec_getheight(s);
    ypos_error = fgetpos((FILE *) file, &ypos);
    fprintf((FILE *) file, "%10lu\n", y_0);
  }
  fwrite(start, len, 1, (FILE *) file);
  return y == ymax - 1;
}
