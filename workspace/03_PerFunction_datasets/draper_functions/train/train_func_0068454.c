color_system_free(struct color_system *colors)
{
  enum color_std stdcolor;

  for (stdcolor= color_std_begin(); stdcolor!= color_std_end();
       stdcolor= color_std_next(stdcolor)) {
    rgbcolor_destroy(*(colors->stdcolors + stdcolor));
  }

  free(colors->stdcolors);

  free(colors);
}
