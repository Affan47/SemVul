dbxout_source_line (unsigned int lineno, const char *filename)
{
  dbxout_source_file (asmfile, filename);

#ifdef ASM_OUTPUT_SOURCE_LINE
  dbxout_source_line_counter += 1;
  ASM_OUTPUT_SOURCE_LINE (asmfile, lineno, dbxout_source_line_counter);
#else
  fprintf (asmfile, "%s%d,0,%d\n", ASM_STABD_OP, N_SLINE, lineno);
#endif
}
