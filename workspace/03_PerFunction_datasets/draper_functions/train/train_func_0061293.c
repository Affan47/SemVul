locali_freeLimdfsstackelem (DECLAREPTRDFSSTATE (aliasstate))
{
  LocaliColumn *column = (LocaliColumn *) aliasstate;

  if (column ->colvalues != NULL)
  {
    ATADDRESS("free ",column);
    gt_free(column->colvalues);
    column->colvalues = NULL;
    column->lenval = 0;
  }
}
