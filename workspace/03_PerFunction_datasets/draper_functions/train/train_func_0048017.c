gt_marksubstring_delete(Gtmarksubstring *mark,bool withbits)
{
  if (mark != NULL)
  {
    if (withbits)
    {
      gt_free(mark->bits);
    }
    gt_free(mark);
  }
}
