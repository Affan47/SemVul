aarch64_print_extension (void)
{
  const struct aarch64_option_extension *opt = NULL;

  for (opt = all_extensions; opt->name != NULL; opt++)
    if ((aarch64_isa_flags & opt->flags_on) == opt->flags_on)
      asm_fprintf (asm_out_file, "+%s", opt->name);

  asm_fprintf (asm_out_file, "\n");
}
