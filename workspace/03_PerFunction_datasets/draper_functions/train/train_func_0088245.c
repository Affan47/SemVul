output_macinfo (void)
{
  unsigned i;
  unsigned long length = VEC_length (macinfo_entry, macinfo_table);
  macinfo_entry *ref;

  if (! length)
    return;

  for (i = 0; VEC_iterate (macinfo_entry, macinfo_table, i, ref); i++)
    {
      switch (ref->code)
	{
	  case DW_MACINFO_start_file:
	    {
	      int file_num = maybe_emit_file (lookup_filename (ref->info));
	      dw2_asm_output_data (1, DW_MACINFO_start_file, "Start new file");
	      dw2_asm_output_data_uleb128
			(ref->lineno, "Included from line number %lu",
			 			(unsigned long)ref->lineno);
	      dw2_asm_output_data_uleb128 (file_num, "file %s", ref->info);
	    }
	    break;
	  case DW_MACINFO_end_file:
	    dw2_asm_output_data (1, DW_MACINFO_end_file, "End file");
	    break;
	  case DW_MACINFO_define:
	    dw2_asm_output_data (1, DW_MACINFO_define, "Define macro");
	    dw2_asm_output_data_uleb128 (ref->lineno, "At line number %lu",
			 			(unsigned long)ref->lineno);
	    dw2_asm_output_nstring (ref->info, -1, "The macro");
	    break;
	  case DW_MACINFO_undef:
	    dw2_asm_output_data (1, DW_MACINFO_undef, "Undefine macro");
	    dw2_asm_output_data_uleb128 (ref->lineno, "At line number %lu",
			 			(unsigned long)ref->lineno);
	    dw2_asm_output_nstring (ref->info, -1, "The macro");
	    break;
	  default:
	   fprintf (asm_out_file, "%s unrecognized macinfo code %lu\n",
	     ASM_COMMENT_START, (unsigned long)ref->code);
	  break;
	}
    }
}
