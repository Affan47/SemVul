lbitset_not (bitset dst, bitset src)
{
  lbitset_elt *selt;
  lbitset_elt *delt;
  bitset_windex i;
  unsigned int j;
  bitset_windex windex;

  windex = (BITSET_SIZE_ (dst) + BITSET_WORD_BITS - 1) / BITSET_WORD_BITS;

  for (i = 0; i < windex; i += LBITSET_ELT_WORDS)
    {


      selt = lbitset_elt_find (src, i, LBITSET_SUBST);
      delt = lbitset_elt_find (dst, i, LBITSET_CREATE);

      for (j = 0; j < LBITSET_ELT_WORDS; j++)
        delt->words[j] = ~selt->words[j];
    }
  lbitset_unused_clear (dst);
  lbitset_weed (dst);
  return;
}
