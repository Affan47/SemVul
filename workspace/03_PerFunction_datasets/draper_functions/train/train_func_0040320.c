arm_output_ttype (rtx x)
{
  fputs ("\t.word\t", asm_out_file);
  output_addr_const (asm_out_file, x);

  if (GET_CODE (x) != CONST_INT)
    fputs ("(TARGET2)", asm_out_file);
  fputc ('\n', asm_out_file);

  return TRUE;
}
