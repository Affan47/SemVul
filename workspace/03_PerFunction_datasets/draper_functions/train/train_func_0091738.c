static_line (FILE *fp, gamgi_bool lights, float *color,
double *start, double *end, int width, gamgi_bool *error)
{
char string[GAMGI_ENGINE_LINE];

gamgi_io_file_fprintf (fp, "<Shape>\n", error);
gamgi_io_file_fprintf (fp, "<Appearance>\n", error);
if (lights == TRUE)
  sprintf (string, "<Material diffuseColor=\"%.*f %.*f %.*f\"/>\n",
  GAMGI_MATH_DECIMAL_COLOR, color[0],
  GAMGI_MATH_DECIMAL_COLOR, color[1],
  GAMGI_MATH_DECIMAL_COLOR, color[2]);
else
  sprintf (string, "<Material emissiveColor=\"%.*f %.*f %.*f\"/>\n",
  GAMGI_MATH_DECIMAL_COLOR, color[0],
  GAMGI_MATH_DECIMAL_COLOR, color[1],
  GAMGI_MATH_DECIMAL_COLOR, color[2]);
gamgi_io_file_fprintf (fp, string, error);

sprintf (string, "<LineProperties linewidthScaleFactor=\"%d\"/>\n", width);
gamgi_io_file_fprintf (fp, string, error);
gamgi_io_file_fprintf (fp, "</Appearance>\n", error);

gamgi_io_file_fprintf (fp, "<IndexedLineSet coordIndex=\"0 1 -1\">\n", error);
sprintf (string, "<Coordinate point=\"%.*f %.*f %.*f %.*f %.*f %.*f\"/>\n",
gamgi->gamgi->length, start[0],
gamgi->gamgi->length, start[1],
gamgi->gamgi->length, start[2],
gamgi->gamgi->length, end[0],
gamgi->gamgi->length, end[1],
gamgi->gamgi->length, end[2]);
gamgi_io_file_fprintf (fp, string, error);
gamgi_io_file_fprintf (fp, "</IndexedLineSet>\n", error);
gamgi_io_file_fprintf (fp, "</Shape>\n", error);
}
