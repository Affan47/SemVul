gt_randomcodes_idx2mincode(const GtRandomcodesinfo *fci,
                                            unsigned long idx)
{
  gt_assert(idx <= fci->differentcodes);
  if (idx == 0)
  {
    return 0;
  }
  else
  {
    return fci->allrandomcodes[idx-1];
  }
}
