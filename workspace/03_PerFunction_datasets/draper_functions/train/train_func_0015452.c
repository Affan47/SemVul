Fd_Element_V_To_Xi(int i, WamWord **array, Range *v)
{
  WamWord *fdv_adr = array[i];

  if (Fd_Variable_Is_Ground(fdv_adr))
    return Fd_Tell_Int_Range(fdv_adr, v);

  return Fd_Tell_Range_Range(fdv_adr, v);
}
