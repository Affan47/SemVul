n_rmmalloc(int size)
{
  rmmalloc_entry newentry;
  newentry.data = n_malloc(size);
  LEadd(rmmalloc_list, newentry);
  return newentry.data;
}
