ListTypeInfo(FILE *file,ExceptionInfo *exception)
{
  char
    weight[MaxTextExtent];

  const char
    *family,
    *glyphs,
    *name,
    *path,
    *stretch,
    *style;

  const TypeInfo
    **type_info;

  register ssize_t
    i;

  size_t
    number_fonts;

  if (file == (FILE *) NULL)
    file=stdout;
  number_fonts=0;
  type_info=GetTypeInfoList("*",&number_fonts,exception);
  if (type_info == (const TypeInfo **) NULL)
    return(MagickFalse);
  *weight='\0';
  path=(const char *) NULL;
  for (i=0; i < (ssize_t) number_fonts; i++)
  {
    if (type_info[i]->stealth != MagickFalse)
      continue;
    if (((path == (const char *) NULL) ||
         (LocaleCompare(path,type_info[i]->path) != 0)) &&
         (type_info[i]->path != (char *) NULL))
      (void) FormatLocaleFile(file,"\nPath: %s\n",type_info[i]->path);
    path=type_info[i]->path;
    name="unknown";
    if (type_info[i]->name != (char *) NULL)
      name=type_info[i]->name;
    family="unknown";
    if (type_info[i]->family != (char *) NULL)
      family=type_info[i]->family;
    style=CommandOptionToMnemonic(MagickStyleOptions,type_info[i]->style);
    stretch=CommandOptionToMnemonic(MagickStretchOptions,type_info[i]->stretch);
    glyphs="unknown";
    if (type_info[i]->glyphs != (char *) NULL)
      glyphs=type_info[i]->glyphs;
    (void) FormatLocaleString(weight,MaxTextExtent,"%.20g",(double)
      type_info[i]->weight);
    (void) FormatLocaleFile(file,"  Font: %s\n",name);
    (void) FormatLocaleFile(file,"    family: %s\n",family);
    (void) FormatLocaleFile(file,"    style: %s\n",style);
    (void) FormatLocaleFile(file,"    stretch: %s\n",stretch);
    (void) FormatLocaleFile(file,"    weight: %s\n",weight);
    (void) FormatLocaleFile(file,"    glyphs: %s\n",glyphs);
  }
  (void) fflush(file);
  type_info=(const TypeInfo **) RelinquishMagickMemory((void *) type_info);
  return(MagickTrue);
}
