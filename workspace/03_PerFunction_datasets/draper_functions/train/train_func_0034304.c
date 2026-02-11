recursive_free(void **alloc, int level)
{
  if (!alloc)
    return;

  if (level)
  {
    int i;
    for (i= 0; i < LF_DYNARRAY_LEVEL_LENGTH; i++)
      recursive_free(alloc[i], level-1);
    my_free(alloc);
  }
  else
    my_free(alloc[-1]);
}
