c_common_write_pch (void)
{
  char *buf;
  long asm_file_end;
  long written;
  struct c_pch_header h;

  timevar_push (TV_PCH_SAVE);

  targetm.prepare_pch_save ();

  (*debug_hooks->handle_pch) (1);

  cpp_write_pch_deps (parse_in, pch_outfile);

  asm_file_end = ftell (asm_out_file);
  h.asm_size = asm_file_end - asm_file_startpos;

  if (fwrite (&h, sizeof (h), 1, pch_outfile) != 1)
    fatal_error ("can%'t write %s: %m", pch_file);

  buf = XNEWVEC (char, 16384);

  if (fseek (asm_out_file, asm_file_startpos, SEEK_SET) != 0)
    fatal_error ("can%'t seek in %s: %m", asm_file_name);

  for (written = asm_file_startpos; written < asm_file_end; )
    {
      long size = asm_file_end - written;
      if (size > 16384)
	size = 16384;
      if (fread (buf, size, 1, asm_out_file) != 1)
	fatal_error ("can%'t read %s: %m", asm_file_name);
      if (fwrite (buf, size, 1, pch_outfile) != 1)
	fatal_error ("can%'t write %s: %m", pch_file);
      written += size;
    }
  free (buf);


  if (fseek (asm_out_file, 0, SEEK_END) != 0)
    fatal_error ("can%'t seek in %s: %m", asm_file_name);

  gt_pch_save (pch_outfile);

  timevar_push (TV_PCH_CPP_SAVE);
  cpp_write_pch_state (parse_in, pch_outfile);
  timevar_pop (TV_PCH_CPP_SAVE);

  if (fseek (pch_outfile, 0, SEEK_SET) != 0
      || fwrite (get_ident (), IDENT_LENGTH, 1, pch_outfile) != 1)
    fatal_error ("can%'t write %s: %m", pch_file);

  fclose (pch_outfile);

  timevar_pop (TV_PCH_SAVE);
}
