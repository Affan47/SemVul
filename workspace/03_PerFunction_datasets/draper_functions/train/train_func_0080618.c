print_symbol_info_sysv (struct extended_symbol_info *info, bfd *abfd)
{
  print_symname ("%-20s|", SYM_NAME (info), abfd);

  if (bfd_is_undefined_symclass (SYM_TYPE (info)))
    {
      if (print_width == 32)
	printf ("        ");
      else
	printf ("                ");
    }
  else
    print_value (abfd, SYM_VALUE (info));

  printf ("|   %c  |", SYM_TYPE (info));

  if (SYM_TYPE (info) == '-')
    {

      printf ("%18s|  ", SYM_STAB_NAME (info));
      printf (desc_format, SYM_STAB_DESC (info));
      printf ("|     |");
    }
  else
    {

      if (info->elfinfo)
	printf ("%18s|",
		get_symbol_type (ELF_ST_TYPE (info->elfinfo->internal_elf_sym.st_info)));
      else
	printf ("                  |");

      if (SYM_SIZE (info))
	print_value (abfd, SYM_SIZE (info));
      else
	{
	  if (print_width == 32)
	    printf ("        ");
	  else
	    printf ("                ");
	}

      if (info->elfinfo)
	printf("|     |%s", info->elfinfo->symbol.section->name);
      else
	printf("|     |");
    }
}
