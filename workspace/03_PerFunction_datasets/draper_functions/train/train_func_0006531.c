moreStrs(ClpEntry *ce, int newNumStrs)  {
  Str  *newStrs;
  int  i;

  assert(newNumStrs > ce->numStrs);
  newStrs = wms_malloc(newNumStrs * sizeof(Str));
  for (i = 0;  i < ce->numStrs;  ++i)  {
    newStrs[i] = ce->storage.strList[i];
  }
  for (;  i < newNumStrs;  ++i)  {
    str_init(&newStrs[i]);
  }
  wms_free(ce->storage.strList);
  ce->storage.strList = newStrs;
}
