ovgroupunmap(void) {
  GROUPDATABLOCK	*gdb, *gdbnext;
  int			i;
  GIBLIST		*giblist, *giblistnext;

  for (i = 0 ; i < GROUPDATAHASHSIZE ; i++) {
    for (gdb = groupdatablock[i] ; gdb != NULL ; gdb = gdbnext) {
      gdbnext = gdb->next;
      free(gdb);
    }
    groupdatablock[i] = NULL;
  }
  for (giblist = Giblist ; giblist != NULL ; giblist = giblistnext) {
    giblistnext = giblist->next;
    free(giblist);
  }
  Giblist = NULL;
  if (!Cache && (Gib != NULL)) {
    free(Gib);
    Gib = NULL;
    if (Cachesearch != NULL) {
      free(Cachesearch->group);
      free(Cachesearch);
      Cachesearch = NULL;
    }
  }
}
