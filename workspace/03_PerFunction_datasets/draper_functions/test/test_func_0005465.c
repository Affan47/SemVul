Arguments_free(ARGUMENTS *ar) {
  if (ar) {
    FREEPARAM *fr;
    FREEPARAM *next;

    fr=ar->params;
    while(fr) {
      next=fr->next;
      FreeParam_free(fr);
      fr=next;
    }
    free(ar);
  }
}
