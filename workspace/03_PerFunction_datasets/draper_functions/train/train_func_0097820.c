main (int argc, char **argv)
{
  progname = "genconstants";

  if (init_md_reader_args (argc, argv) != SUCCESS_EXIT_CODE)
    return (FATAL_EXIT_CODE);


  puts ("/* Generated automatically by the program `genconstants'");
  puts ("   from the machine description file `md'.  */\n");
  puts ("#ifndef GCC_INSN_CONSTANTS_H");
  puts ("#define GCC_INSN_CONSTANTS_H\n");

  traverse_md_constants (print_md_constant, stdout);

  puts ("\n#endif /* GCC_INSN_CONSTANTS_H */");

  if (ferror (stdout) || fflush (stdout) || fclose (stdout))
    return FATAL_EXIT_CODE;

  return SUCCESS_EXIT_CODE;
}
