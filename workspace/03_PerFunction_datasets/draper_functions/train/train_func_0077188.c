ebitset_equal_p (bitset dst, bitset src)
{
  ebitset_elts *selts;
  ebitset_elts *delts;
  bitset_windex j;

  if (src == dst)
    return true;

  ebitset_weed (dst);
  ebitset_weed (src);

  if (EBITSET_SIZE (src) != EBITSET_SIZE (dst))
    return false;

  selts = EBITSET_ELTS (src);
  delts = EBITSET_ELTS (dst);

  for (j = 0; j < EBITSET_SIZE (src); j++)
    {
      unsigned int i;
      ebitset_elt *selt = selts[j];
      ebitset_elt *delt = delts[j];

      if (!selt && !delt)
        continue;
      if ((selt && !delt) || (!selt && delt))
        return false;

      for (i = 0; i < EBITSET_ELT_WORDS; i++)
        if (EBITSET_WORDS (selt)[i] != EBITSET_WORDS (delt)[i])
          return false;
    }
  return true;
}
