GROUPexpand(int mode) {
  int	i;
  int	flag = 0;

  if (GROUPheader) {
    if (munmap((void *)GROUPheader, GROUPfilesize(GROUPcount)) < 0) {
      syswarn("buffindexed: Could not munmap group.index in GROUPexpand");
      return false;
    }
  }
  GROUPcount += 1024;
  if (ftruncate(GROUPfd, GROUPfilesize(GROUPcount)) < 0) {
    syswarn("buffindexed: Could not extend group.index");
    return false;
  }
  if (mode & OV_READ)
    flag |= PROT_READ;
  if (mode & OV_WRITE) {


    flag |= PROT_WRITE|PROT_READ;
  }
  GROUPheader = mmap(0, GROUPfilesize(GROUPcount), flag, MAP_SHARED,
		     GROUPfd, 0);
  if (GROUPheader == MAP_FAILED) {
    syswarn("buffindexed: Could not mmap group.index in GROUPexpand");
    return false;
  }
  GROUPentries = (GROUPENTRY *)((char *)GROUPheader + sizeof(GROUPHEADER));
  if (GROUPheader->magic != GROUPHEADERMAGIC) {
    GROUPheader->magic = GROUPHEADERMAGIC;
    GROUPLOCclear(&GROUPheader->freelist);
    for (i = 0; i < GROUPHEADERHASHSIZE; i++)
      GROUPLOCclear(&GROUPheader->hash[i]);
  }

  for (i = GROUPcount - 1; (GROUPcount - 1024) <= i; i--) {
    GROUPentries[i].next = GROUPheader->freelist;
    GROUPheader->freelist.recno = i;
  }
  return true;
}
