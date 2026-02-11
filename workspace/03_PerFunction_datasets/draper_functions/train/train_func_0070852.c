MarkCacheHash(
  char * ptr,
  int  modulus)
{
    int val = 0;
    MarkCacheKey *entry;

    entry = (MarkCacheKey *) ptr;

    val = (int) (ptrint) entry->f;
    val = val * 997 + (int) (ptrint) entry->c;

    return ((val < 0) ? -val : val) % modulus;

}
