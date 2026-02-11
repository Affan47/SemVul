minilisp_info(void)
{
  time_t tim = time(0);
  const char *dat = ctime(&tim);
  printf("--- begin info -- %s", dat);
  printf("symbols: %d symbols in %d buckets\n",
         symbols->nelems, symbols->nbuckets);
  if (gc.debug)
    printf("gc.debug: true\n");
  if (gc.lock)
    printf("gc.locked: true, %d requests\n", gc.request);
  printf("gc.pairs: %d free, %d total\n", gc.pairs_free, gc.pairs_total);
  printf("gc.objects: %d free, %d total\n", gc.objs_free, gc.objs_total);
  printf("--- end info -- %s", dat);
}
