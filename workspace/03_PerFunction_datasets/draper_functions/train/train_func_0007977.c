pch_init (void)
{
  FILE *f;
  struct c_pch_validity v;
  void *target_validity;
  static const char partial_pch[IDENT_LENGTH] = "gpcWrite";
  unsigned int current_flags_info = 0;

  if (! pch_file)
    return;

  if (flag_unit_at_a_time)
    current_flags_info |= FLAG_UNIT_AT_A_TIME_SET;

  f = fopen (pch_file, "w+b");
  if (f == NULL)
    fatal_error ("can't create precompiled header %s: %m", pch_file);
  pch_outfile = f;

  if (strlen (host_machine) > 255 || strlen (target_machine) > 255
      || strlen (version_string) > 255)
    abort ();

  v.host_machine_length = strlen (host_machine);
  v.target_machine_length = strlen (target_machine);
  v.version_length = strlen (version_string);
  v.debug_info_type = write_symbols;
  v.flags_info = current_flags_info;
  v.pch_init = &pch_init;
  target_validity = targetm.get_pch_validity (&v.target_data_length);

  if (fwrite (partial_pch, IDENT_LENGTH, 1, f) != 1
      || fwrite (&v, sizeof (v), 1, f) != 1
      || fwrite (host_machine, v.host_machine_length, 1, f) != 1
      || fwrite (target_machine, v.target_machine_length, 1, f) != 1
      || fwrite (version_string, v.version_length, 1, f) != 1
      || fwrite (target_validity, v.target_data_length, 1, f) != 1)
    fatal_error ("can't write to %s: %m", pch_file);


  if (asm_file_name == NULL
      || strcmp (asm_file_name, "-") == 0)
    fatal_error ("`%s' is not a valid output file", asm_file_name);

  asm_file_startpos = ftell (asm_out_file);


  (*debug_hooks->handle_pch) (0);

  cpp_save_state (parse_in, f);
}
