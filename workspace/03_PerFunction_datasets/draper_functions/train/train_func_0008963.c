gt_marksubstring_mark(Gtmarksubstring *mark,GtCodetype code)
{
  code = (code >> (GtCodetype) mark->shiftright) & mark->mask;

  gt_assert(code < mark->entries);
  if (!GT_ISIBITSET(mark->bits,code))
  {
    GT_SETIBIT(mark->bits,code);
  }
}
