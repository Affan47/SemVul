ListColorInfo(FILE *file,
  ExceptionInfo *exception)
{
  char
    tuple[MaxTextExtent];

  const char
    *path;

  const ColorInfo
    **color_info;

  register ssize_t
    i;

  size_t
    number_colors;


  if (file == (const FILE *) NULL)
    file=stdout;
  color_info=GetColorInfoList("*",&number_colors,exception);
  if (color_info == (const ColorInfo **) NULL)
    return(MagickFalse);
  path=(const char *) NULL;
  for (i=0; i < (ssize_t) number_colors; i++)
  {
    if (color_info[i]->stealth != MagickFalse)
      continue;
    if ((path == (const char *) NULL) ||
        (LocaleCompare(path,color_info[i]->path) != 0))
      {
        if (color_info[i]->path != (char *) NULL)
          (void) FormatLocaleFile(file,"\nPath: %s\n\n",color_info[i]->path);
        (void) FormatLocaleFile(file,
          "Name                  Color                  "
          "                       Compliance\n");
        (void) FormatLocaleFile(file,
          "-------------------------------------------------"
          "------------------------------\n");
      }
    path=color_info[i]->path;
    (void) FormatLocaleFile(file,"%-21.21s ",color_info[i]->name);
    GetColorTuple(&color_info[i]->color,MagickFalse,tuple);
    (void) FormatLocaleFile(file,"%-45.45s ",tuple);
    if ((color_info[i]->compliance & SVGCompliance) != 0)
      (void) FormatLocaleFile(file,"SVG ");
    if ((color_info[i]->compliance & X11Compliance) != 0)
      (void) FormatLocaleFile(file,"X11 ");
    if ((color_info[i]->compliance & XPMCompliance) != 0)
      (void) FormatLocaleFile(file,"XPM ");
    (void) FormatLocaleFile(file,"\n");
  }
  color_info=(const ColorInfo **) RelinquishMagickMemory((void *) color_info);
  (void) fflush(file);
  return(MagickTrue);
}
