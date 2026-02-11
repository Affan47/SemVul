sti_compar(const void *key, const void *elem) {
  const adns_status *st= key;
  const struct stinfo *sti= elem;

  adns_status here, min, max;

  here= *st;
  min= (sti==stinfos) ? 0 : sti[-1].stmax+1;
  max= sti->stmax;

  return here < min  ? -1 : here > max ? 1 : 0;
}
