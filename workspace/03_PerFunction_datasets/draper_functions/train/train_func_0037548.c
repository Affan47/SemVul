gt_newCompositionList(unsigned blockSize, unsigned alphabetSize)
{
  struct compList *newList = NULL;
  if (!(newList = gt_calloc(1, sizeof (struct compList))))
    return NULL;
  if (!gt_initCompositionList(newList, blockSize, alphabetSize))
  {
    gt_free(newList);
    return NULL;
  }
  return newList;
}
