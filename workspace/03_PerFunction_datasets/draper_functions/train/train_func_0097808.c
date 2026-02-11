CNFS_setcurrent(METACYCBUFF *metacycbuff) {
  CYCBUFF	*cycbuff;
  int		i, currentcycbuff = 0, order = -1;
  bool		foundcurrent = false;
  for (i = 0 ; i < metacycbuff->count ; i++) {
    cycbuff = metacycbuff->members[i];
    if (strncmp(cycbuff->metaname, metacycbuff->name, CNFSNASIZ) != 0) {

      cycbuff->order = i + 1;
      cycbuff->currentbuff = false;
      strncpy(cycbuff->metaname, metacycbuff->name, CNFSLASIZ);
      cycbuff->needflush = true;
      continue;
    }
    if (foundcurrent == false && cycbuff->currentbuff == true) {
      currentcycbuff = i;
      foundcurrent = true;
    }
    if (foundcurrent == false || order == -1 || order > cycbuff->order) {

      currentcycbuff = i;
      order = cycbuff->order;
    }
    if (cycbuff->order != i + 1) {

      cycbuff->order = i + 1;
      cycbuff->needflush = true;
    }
  }

  if (foundcurrent == false) {
    currentcycbuff = 0;
  }
  for (i = 0 ; i < metacycbuff->count ; i++) {
    cycbuff = metacycbuff->members[i];
    if (currentcycbuff == i && cycbuff->currentbuff == false) {
      cycbuff->currentbuff = true;
      cycbuff->needflush = true;
    }
    if (currentcycbuff != i && cycbuff->currentbuff == true) {
      cycbuff->currentbuff = false;
      cycbuff->needflush = true;
    }
    if (cycbuff->needflush == true && !CNFSflushhead(cycbuff))
	return false;
  }
  metacycbuff->memb_next = currentcycbuff;
  return true;
}
