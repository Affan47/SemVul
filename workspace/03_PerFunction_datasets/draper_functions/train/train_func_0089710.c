bitmap_single_bit_set_p (const_bitmap a)
{
  unsigned long count = 0;
  const bitmap_element *elt;
  unsigned ix;

  if (bitmap_empty_p (a))
    return false;

  elt = a->first;


  if (elt->next != NULL)
    return false;

  for (ix = 0; ix != BITMAP_ELEMENT_WORDS; ix++)
    {
#if GCC_VERSION >= 3400


      count += __builtin_popcountl (elt->bits[ix]);
#else
      count += bitmap_popcount (elt->bits[ix]);
#endif
      if (count > 1)
	return false;
    }

  return count == 1;
}
