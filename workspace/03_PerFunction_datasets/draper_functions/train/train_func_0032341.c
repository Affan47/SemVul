DetectOverlappingLines(void)
{


  int i;
  int *array = (int *)UtilCalloc(num_linedefs * sizeof(int));
  int count = 0;

  DisplayTicker();


  for (i=0; i < num_linedefs; i++)
    array[i] = i;

  qsort(array, num_linedefs, sizeof(int), LineStartCompare);

  for (i=0; i < num_linedefs - 1; i++)
  {
    int j;

    for (j = i+1; j < num_linedefs; j++)
    {
      if (LineStartCompare(array + i, array + j) != 0)
        break;

      if (LineEndCompare(array + i, array + j) == 0)
      {
        linedef_t *A = lev_linedefs[array[i]];
        linedef_t *B = lev_linedefs[array[j]];


        B->overlap = A->overlap ? A->overlap : A;

        count++;
      }
    }
  }

  if (count > 0)
  {
      PrintVerbose("Detected %d overlapped linedefs\n", count);
  }

  UtilFree(array);
}
