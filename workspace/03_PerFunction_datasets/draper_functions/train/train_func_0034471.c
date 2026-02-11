Fd_New_Int_Variable(int n)
{
  WamWord *fdv_adr = CS;

  FD_Tag_Value(fdv_adr) = Tag_INT(n);
  FD_INT_Date(fdv_adr) = DATE;
  Queue_Date_At_Push(fdv_adr) = 0;
  Queue_Propag_Mask(fdv_adr) = 0;
  Queue_Next_Fdv_Adr(fdv_adr) = (WamWord) NULL;

  Range_Stamp(fdv_adr) = STAMP;
  Nb_Elem(fdv_adr) = 1;
  Range_Init_Interval(Range(fdv_adr), n, n);

  CS += FD_INT_VARIABLE_FRAME_SIZE;

  return fdv_adr;
}
