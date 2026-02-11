opt_print_help(struct opt_odb_t *odb,
	       FILE *fd)
{
  struct opt_opt_t *opt;


  print_option_header(odb, fd);

  fprintf(fd, "#\n");
  fprintf(fd, "%-16s %-16s # %12s # %-22s\n",
	  "# -option", "<args>", "<default>", "description");
  fprintf(fd, "#\n");


  for (opt=builtin_options; opt != NULL; opt=opt->next)
    print_help(opt, fd);


  for (opt=odb->options; opt != NULL; opt=opt->next)
    print_help(opt, fd);


  print_option_notes(odb, fd);
}
