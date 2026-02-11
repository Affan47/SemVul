gt_marksubstring_bits_null(GT_UNUSED const Gtmarksubstring *mark,bool null)
{
  if (null)
  {
    gt_assert(mark->bits == NULL);
  } else
  {
    gt_assert(mark->bits != NULL);
  }
}
