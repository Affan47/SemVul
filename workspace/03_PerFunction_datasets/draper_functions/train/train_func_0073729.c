gt_marksubstring_new(unsigned int numofchars,
                                      unsigned int kmersize,
                                      bool usesuffix,
                                      unsigned int units)
{
  Gtmarksubstring *mark;

  mark = gt_malloc(sizeof (*mark));
  gt_assert(kmersize >= units);
  mark->units = units;
  mark->entries = gt_power_for_small_exponents(numofchars,units);
  if (usesuffix)
  {
    mark->shiftright = 0;
    mark->mask = (GtCodetype) (mark->entries-1);
  } else
  {
    mark->shiftright = GT_MULT2(kmersize - units);
    mark->mask = ~(GtCodetype) 0;
  }
  GT_INITBITTAB(mark->bits,mark->entries);
  mark->size = sizeof (GtBitsequence) * GT_NUMOFINTSFORBITS(mark->entries);
  return mark;
}
