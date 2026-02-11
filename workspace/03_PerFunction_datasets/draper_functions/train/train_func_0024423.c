array_compare(
  const char * array1,
  const char * array2)
{
    int i;
    int *intarray1, *intarray2;

    intarray1 = (int *) array1;
    intarray2 = (int *) array2;

    for (i = 0; i < numvars; i++) {
	if (intarray1[i] != intarray2[i]) return(1);
    }
    return(0);

}
