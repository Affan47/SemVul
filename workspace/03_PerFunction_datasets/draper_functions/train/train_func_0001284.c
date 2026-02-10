ovclosesearch(void *handle, bool freeblock) {
  OVSEARCH		*search = (OVSEARCH *)handle;
  GROUPDATABLOCK	*gdb;
  int			i;
#ifdef OV_DEBUG
  GROUPENTRY	*ge;
  GROUPLOC	gloc;
#endif

  for (i = 0 ; i < GROUPDATAHASHSIZE ; i++) {
    for (gdb = groupdatablock[i] ; gdb != NULL ; gdb = gdb->next) {
      if (gdb->mmapped)
	munmap(gdb->addr, gdb->len);
    }
  }
  if (search->gdb.mmapped)
    munmap(search->gdb.addr, search->gdb.len);
  if (freeblock) {
#ifdef OV_DEBUG
    gloc = GROUPfind(search->group, false);
    if (!GROUPLOCempty(gloc)) {
      ge = &GROUPentries[gloc.recno];
      freegroupblock(ge);
    }
#else
    freegroupblock();
#endif
  }
  ovgroupunmap();
  if (Cache) {
    Cachesearch = search;
  } else {
    free(search->group);
    free(search);
  }
  return;
}
