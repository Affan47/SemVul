static_unscale (FILE *fp, double scale, gamgi_bool *error)
{
if (fabs (scale - 1.0) > GAMGI_MATH_TOLERANCE)
  gamgi_io_file_fprintf(fp, "</Transform>\n</Transform>\n</Transform>\n", error);
}
