g15r_requestG15DefaultFont (int size)
{
  char filename[128];
  if (size<0)  size=0;
  if (size>39) size=39;


  if(!defaultfont[size]) {
    snprintf(filename,128,"%s/G15/default-%.2i.fnt",G15FONT_DIR,size);
    defaultfont[size] = g15r_loadG15Font(filename);
    if((defaultfont[size])==NULL) {
          fprintf(stderr,"libg15render: Unable to load font \"%s\"\n",filename);
          return NULL;
      }
  }
  return defaultfont[size];
}
