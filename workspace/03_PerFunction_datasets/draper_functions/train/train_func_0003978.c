reorderPriorityList (void)
{
  int i, j ;
  static int thisTime = 4;


  if (--thisTime > 0)
    return ;

  thisTime = 4;

  for (i = j = 0; i < priorityCount; i++)
    if (priorityList [i] != NULL)
      {
        if (i != j)
          priorityList [j] = priorityList [i] ;
        j++ ;
      }

  for (i = j; i < priorityCount; i++)
    priorityList [ i ] = NULL;

  priorityCount = j;

  qsort (priorityList, (size_t)priorityCount, sizeof (EndPoint), &hitCompare);
}
