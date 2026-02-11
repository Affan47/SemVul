Indomain_Max_Alt_0(void)
{
  WamWord *fdv_adr;
  Range *range;
  int cur, end;

  Update_Choice_Point((CodePtr) Prolog_Predicate(INDOMAIN_MAX_ALT, 0), 0);

  fdv_adr = (WamWord *) AB(B, 0);
  range = (Range *) AB(B, 1);
  end = AB(B, 2);
  cur = AB(B, 3);

  cur = Range_Next_Before(range, cur);

  SYS_VAR_FD_BCKTS++;

  if (cur != end)
    {
#if 0
      AB(B, 0) = (WamWord) fdv_adr;
      AB(B, 1) = (WamWord) range;
      AB(B, 2) = end;
#endif
      AB(B, 3) = cur;
    }
  else if (Extra_Cstr(fdv_adr))
    Update_Choice_Point((CodePtr) Prolog_Predicate(EXTRA_CSTR_ALT, 0), 0);
  else
    Delete_Choice_Point(0);

  return Fd_Assign_Value(fdv_adr, cur);
}
