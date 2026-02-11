line_hash(const int *ar, int nr)
{
  int i;
  unsigned h = 0;
  for (i = 0; i < nr; i++) {
    h += ar[i];
  }
  return (h % HASH_SIZE);
}
