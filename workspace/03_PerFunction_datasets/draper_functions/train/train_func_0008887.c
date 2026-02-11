dw2_asm_output_addr_rtx (int size, rtx addr,
			 const char *comment, ...)
{
  va_list ap;

  va_start (ap, comment);

  dw2_assemble_integer (size, addr);

  if (flag_debug_asm && comment)
    {
      fprintf (asm_out_file, "\t%s ", ASM_COMMENT_START);
      vfprintf (asm_out_file, comment, ap);
    }
  fputc ('\n', asm_out_file);

  va_end (ap);
}
