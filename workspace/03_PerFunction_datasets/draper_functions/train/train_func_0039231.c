__find_freq_item(int len)
{
  struct __mpi_stats_freq_item* ret = NULL;
  unsigned i;
  for(i=0; i<__mpi_stats_freq.nb_items; i++) {
    ret = ITH_VALUE(i, &__mpi_stats_freq);
    if(ret->len == len)
      return ret;
  }


  ret = eztrace_array_new_value(&__mpi_stats_freq);
  ret->len = len;
  ret->nb_occur = 0;
  return ret;
}
