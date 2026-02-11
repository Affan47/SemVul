getcolour(const char *name, int def) {
  Status st;
  XColor screen_def, exact_def;
  st= XAllocNamedColor(display,cmap,name,&screen_def,&exact_def);
  fprintf(stdout,"name %s pixel %lu\n",name,screen_def.pixel);
  return st ? screen_def.pixel : def;
}
