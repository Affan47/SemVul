DddmpStrArrayDup (
  char **array    ,
  int n
  )
{
  char **array2;
  int i;

  array2 = DDDMP_ALLOC(char *, n);
  if (array2 == NULL) {
    (void) fprintf (stderr, "DddmpStrArrayDup: Error allocating memory\n");
    fflush (stderr);
    return NULL;
  }


  for (i=0; i<n; i++) {
    array2[i] = NULL;
  }

  for (i=0; i<n; i++) {
    if (array[i] != NULL) {
      if ((array2[i]=DddmpStrDup(array[i]))==NULL) {
        DddmpStrArrayFree (array2, n);
        return (NULL);
      }
    }
  }

  return (array2);
}
