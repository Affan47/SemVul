calcNstats(unsigned long key, unsigned long long value,
                        void *data)
{
  Nstats *nstats = data;
  unsigned int i;
  nstats->current_len += (key * value);
  nstats->current_num += value;
  for (i = 0; i < (unsigned int) NOF_LIMITS; i++)
  {
    if ((unsigned long long) key > nstats->limit[i])
      nstats->larger_than_limit[i] = nstats->current_num;
  }
  if (nstats->median == 0 && nstats->current_num >= nstats->half_num)
  {
    nstats->median = (unsigned long long) key;
  }
  for (i = 0; i < nstats->nofstats; i++)
  {
    if (!nstats->done[i] && (nstats->current_len >= nstats->min[i]))
    {
      nstats->done[i] = true;
      nstats->nvalue[i] = key;
      nstats->lvalue[i] = (unsigned long) nstats->current_num;
    }
  }
}
