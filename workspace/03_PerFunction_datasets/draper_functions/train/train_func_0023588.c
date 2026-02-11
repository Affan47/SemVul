output_body_line_text(FILE *fp, const cssc_linebuf* plb)
{
  return plb->write(fp) || fputc_failed(fputc('\n', fp));
}
