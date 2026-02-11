gt_randomcodes_find_insert(const GtRandomcodesinfo *fci,
                                               unsigned long code)
{
  const unsigned long *found = NULL, *leftptr = NULL, *midptr, *rightptr = NULL;

  leftptr = fci->allrandomcodes + fci->currentminindex;
  rightptr = fci->allrandomcodes + fci->currentmaxindex;
  if (code < *leftptr)
  {
    return leftptr;
  }
  while (leftptr <= rightptr)
  {
    midptr = leftptr + GT_DIV2((unsigned long) (rightptr-leftptr));
    if (code < *midptr)
    {
      rightptr = midptr - 1;
      if (code > *rightptr)
      {
        return midptr;
      }
      found = midptr;
    } else
    {
      if (code > *midptr)
      {
        leftptr = midptr + 1;
        if (code <= *leftptr)
        {
          return leftptr;
        }
      } else
      {
        return midptr;
      }
    }
  }
  return found;
}
