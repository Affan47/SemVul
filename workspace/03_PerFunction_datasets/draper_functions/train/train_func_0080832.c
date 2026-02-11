qsort_func(const void *el1, const void *el2)
{
  const Item *item1 = *(Item**)el1;
  const Item *item2 = *(Item**)el2;
  time_t time1=item1->get_time();
  time_t time2=item2->get_time();
  return time1<time2 ? -1 : time1>time2 ? 1 : 0;
}
