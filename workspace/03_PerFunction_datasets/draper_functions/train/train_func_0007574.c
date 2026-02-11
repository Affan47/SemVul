gather( ranctx *r, u8 *data, u8 len, u4 terms)
{
  u8 i;
  u4 val = 0;
  u4 mask = (1<<(LOGBUCKETS*terms))-1;
  for (i=0; i<BUCKETS; ++i)
    val = ((val<<LOGBUCKETS)&mask) + ftab[count(ranval(r))];
  for (i=0; i<len; ++i) {
    val = ((val<<LOGBUCKETS)&mask) + ftab[count(ranval(r))];
    ++data[val];
  }
}
