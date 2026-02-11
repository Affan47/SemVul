process_unwind (FILE * file)
{
  struct unwind_handler
  {
    int machtype;
    void (* handler)(FILE *);
  } handlers[] =
  {
    { EM_ARM, arm_process_unwind },
    { EM_IA_64, ia64_process_unwind },
    { EM_PARISC, hppa_process_unwind },
    { EM_TI_C6000, arm_process_unwind },
    { 0, 0 }
  };
  int i;

  if (!do_unwind)
    return;

  for (i = 0; handlers[i].handler != NULL; i++)
    if (elf_header.e_machine == handlers[i].machtype)
      return handlers[i].handler (file);

  printf (_("\nThe decoding of unwind sections for machine type %s is not currently supported.\n"),
	  get_machine_name (elf_header.e_machine));
}
