ebitset_elt_find (bitset bset, bitset_bindex bindex,
                  enum ebitset_find_mode mode)
{
  ebitset_elt *elt;
  bitset_windex size;
  bitset_windex eindex;
  ebitset_elts *elts;

  eindex = bindex / EBITSET_ELT_BITS;

  elts = EBITSET_ELTS (bset);
  size = EBITSET_SIZE (bset);

  if (eindex < size)
    {
      if ((elt = elts[eindex]))
        {
          if (EBITSET_WORDS (elt) == bset->b.cdata)
            return elt;

          EBITSET_CACHE_SET (bset, eindex);
          return elt;
        }
    }


  switch (mode)
    {
    default:
      abort ();

    case EBITSET_FIND:
      return 0;

    case EBITSET_CREATE:
      if (eindex >= size)
        ebitset_resize (bset, bindex);


      elt = ebitset_elt_calloc ();
      ebitset_elt_add (bset, elt, eindex);
      EBITSET_CACHE_SET (bset, eindex);
      return elt;

    case EBITSET_SUBST:
      return &ebitset_zero_elts[0];
    }
}
