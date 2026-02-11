dbxout_source_line (unsigned int lineno, const char *filename,
                    int discriminator ATTRIBUTE_UNUSED,
                    bool is_stmt ATTRIBUTE_UNUSED)
{
  dbxout_source_file (filename);

#ifdef DBX_OUTPUT_SOURCE_LINE
  DBX_OUTPUT_SOURCE_LINE (asm_out_file, lineno, dbxout_source_line_counter);
#else
  if (DBX_LINES_FUNCTION_RELATIVE)
    {
      char begin_label[20];
      dbxout_begin_stabn_sline (lineno);

      ASM_GENERATE_INTERNAL_LABEL (begin_label, "LFBB", scope_labelno);
      dbxout_stab_value_internal_label_diff ("LM", &dbxout_source_line_counter,
					     begin_label);
    }
  else
    dbxout_stabd (N_SLINE, lineno);
#endif
}
