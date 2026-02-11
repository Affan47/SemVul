swapBodyElements(IdArray* ids1, IdArray* ids2, IdArray* relative_dirs)
{
  int index = 0;
  while (true) {
    BodyElementLoop* bel = getBodyElementLoop(index++);
    if (bel==NULL) break;
    bel->swapElements(ids1, ids2, relative_dirs);
  }

}
