dump_cfi_row (FILE *f, dw_cfi_row *row)
{
  dw_cfi_ref cfi;
  unsigned i;

  cfi = row->cfa_cfi;
  if (!cfi)
    {
      dw_cfa_location dummy;
      memset(&dummy, 0, sizeof(dummy));
      dummy.reg = INVALID_REGNUM;
      cfi = def_cfa_0 (&dummy, &row->cfa);
    }
  output_cfi_directive (f, cfi);

  FOR_EACH_VEC_SAFE_ELT (row->reg_save, i, cfi)
    if (cfi)
      output_cfi_directive (f, cfi);
}
