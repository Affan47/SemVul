Scan_Dynamic_Pred_Alt_0(void)
{
  WamWord *alt_info;
  DynScan *scan;
  DynCInf *clause;
  Bool is_last;
  WamWord *adr;
  int i;
  CodePtr scan_alt;

  scan_alt = ALTB(B);
  Update_Choice_Point(scan_alt, 0);

  i = (sizeof(DynScan) + sizeof(WamWord) - 1) / sizeof(WamWord) - 1;

  scan = (DynScan *) &AB(B, i);
  adr = (WamWord *) scan;
  alt_info = (WamWord *) (adr - scan->alt_size_info);

  clause = scan->clause;

  is_last = (Scan_Dynamic_Pred_Next(scan) == NULL);

  if (is_last)
    Delete_Last_Choice_Point();

  return (*scan->alt_fct) (clause, alt_info, is_last);
}
