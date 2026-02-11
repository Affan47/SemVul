addPointerFreedOnExit (char *pointerToFree)
{
  static int totalPointers = 0 ;
  static int nextPointer = 0 ;

  if (nextPointer == 0 || nextPointer == totalPointers - 1)
    {
      register int i;

      totalPointers += 16 ;
      if (PointersFreedOnExit == NULL)
	PointersFreedOnExit = ALLOC (char *, totalPointers) ;
      else
	PointersFreedOnExit =
	  REALLOC (PointersFreedOnExit, char *, totalPointers) ;

      ASSERT (PointersFreedOnExit != NULL) ;

      for (i = nextPointer; i < totalPointers; i++)
	PointersFreedOnExit [i] = NULL;
    }
  PointersFreedOnExit [nextPointer++] = pointerToFree ;
}
