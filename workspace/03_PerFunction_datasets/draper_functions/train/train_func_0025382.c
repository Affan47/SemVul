output_function_exception_table (const char *fnname)
{
  rtx personality = get_personality_function (current_function_decl);


  if (! crtl->uses_eh_lsda)
    return;

  if (personality)
    {
      assemble_external_libcall (personality);

      if (targetm.asm_out.emit_except_personality)
	targetm.asm_out.emit_except_personality (personality);
    }

  switch_to_exception_section (fnname);


  targetm.asm_out.emit_except_table_label (asm_out_file);

  output_one_function_exception_table (0);
  if (crtl->eh.call_site_record[1] != NULL)
    output_one_function_exception_table (1);

  switch_to_section (current_function_section ());
}
