ebitset_resize (bitset src, bitset_bindex n_bits)
{
  bitset_windex oldsize;
  bitset_windex newsize;

  if (n_bits == BITSET_NBITS_ (src))
    return n_bits;

  oldsize = EBITSET_SIZE (src);
  newsize = EBITSET_N_ELTS (n_bits);

  if (oldsize < newsize)
    {
      bitset_windex size;


      if (newsize > EBITSET_ASIZE (src))
        {


          if (oldsize == 0)
            size = newsize;
          else
            size = newsize + newsize / 4;

          EBITSET_ELTS (src)
            = realloc (EBITSET_ELTS (src), size * sizeof (ebitset_elt *));
          EBITSET_ASIZE (src) = size;
        }

      memset (EBITSET_ELTS (src) + oldsize, 0,
              (newsize - oldsize) * sizeof (ebitset_elt *));
    }
  else
    {


      if ((oldsize - newsize) >= oldsize / 2)
        {
          EBITSET_ELTS (src)
            = realloc (EBITSET_ELTS (src), newsize * sizeof (ebitset_elt *));
          EBITSET_ASIZE (src) = newsize;
        }


    }

  BITSET_NBITS_ (src) = n_bits;
  return n_bits;
}
