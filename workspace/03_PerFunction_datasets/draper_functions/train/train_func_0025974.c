gtp_mprintf(const char *fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);

  for (; *fmt; ++fmt) {
    if (*fmt == '%') {
      switch (*++fmt) {
      case 'c':
      {

	int c = va_arg(ap, int);
	putc(c, gtp_output_file);
	break;
      }
      case 'd':
      {
	int d = va_arg(ap, int);
	fprintf(gtp_output_file, "%d", d);
	break;
      }
      case 'f':
      {
	double f = va_arg(ap, double);
	fprintf(gtp_output_file, "%f", f);
	break;
      }
      case 's':
      {
	char *s = va_arg(ap, char *);
	fputs(s, gtp_output_file);
	break;
      }
      case 'm':
      {
	int m = va_arg(ap, int);
	int n = va_arg(ap, int);
        gtp_print_vertex(m, n);
	break;
      }
      case 'C':
      {
	int color = va_arg(ap, int);
	if (color == WHITE)
	  fputs("white", gtp_output_file);
	else if (color == BLACK)
	  fputs("black", gtp_output_file);
	else
	  fputs("empty", gtp_output_file);
	break;
      }
      default:

	fprintf(gtp_output_file, "\n\nUnknown format character '%c'\n", *fmt);
	break;
      }
    }
    else
      putc(*fmt, gtp_output_file);
  }
  va_end(ap);
}
