smartlist_shuffle(smartlist_t *sl)
{
  int i;


  for (i = smartlist_len(sl)-1; i > 0; --i) {
    int j = crypto_rand_int(i+1);
    smartlist_swap(sl, i, j);
  }
}
