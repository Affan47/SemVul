ebitset_weed (bitset bset)
{
  ebitset_elts *elts;
  bitset_windex j;
  bitset_windex count;

  if (EBITSET_ZERO_P (bset))
    return 0;

  elts = EBITSET_ELTS (bset);
  count = 0;
  for (j = 0; j < EBITSET_SIZE (bset); j++)
    {
      ebitset_elt *elt = elts[j];

      if (elt)
        {
          if (ebitset_elt_zero_p (elt))
            {
              ebitset_elt_remove (bset, j);
              count++;
            }
        }
      else
        count++;
    }

  count = j - count;
  if (!count)
    {


      EBITSET_ZERO_SET (bset);
    }
  else
    EBITSET_NONZERO_SET (bset);

  return count;
}
