mk_createWriter(const char *filename) {
  mk_Writer *w = malloc(sizeof(*w));
  if (w == NULL)
    return NULL;

  memset(w, 0, sizeof(*w));

  w->root = mk_createContext(w, NULL, 0);
  if (w->root == NULL) {
    free(w);
    return NULL;
  }

  w->fp = fopen(filename, "wb");
  if (w->fp == NULL) {
    mk_destroyContexts(w);
    free(w);
    return NULL;
  }

  w->timescale = 1000000;

  return w;
}
