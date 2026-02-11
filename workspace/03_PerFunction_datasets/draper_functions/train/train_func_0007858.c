normal3_interp(Interp a, Plist discriminators)
{
  int i, b;
  int **prof = malloc(sizeof(int *) * a->size);
  int *perm  = malloc(sizeof(int) * a->size);
  int size = a->size;
  Interp norm;

  create_profile(a, discriminators);


  for (i = 0; i < size; i++)
    prof[i] = a->profile[i];

  for (i = 0; i < size; i++) {
    int *max = NULL;
    int index_of_max = -1;
    int j;
    for (j = 0; j < size; j++) {
      if (prof[j] != NULL) {
	if (max == NULL ||
	    compare_vecs(prof[j],
			 max, a->num_profile_components) == GREATER_THAN) {
	  index_of_max = j;
	  max = prof[j];
	}
      }
    }
    perm[index_of_max] = i;
    prof[index_of_max] = NULL;
  }

  free(prof);


  norm = permute_interp(a, perm);
  free(perm);


  b = 0;

  norm->blocks[0] = 0;
  for (i = 1; i < norm->size; i++) {
    if (compare_vecs(norm->profile[i-1], norm->profile[i],
		     norm->num_profile_components) != SAME_AS)
      b++;
    norm->blocks[i] = b;
  }
  return norm;
}
