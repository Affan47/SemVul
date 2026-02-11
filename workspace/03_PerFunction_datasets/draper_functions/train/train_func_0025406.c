display_target_list (void)
{
  char *dummy_name;
  int t;
  int ret = 1;

  dummy_name = make_temp_file (NULL);
  for (t = 0; bfd_target_vector[t]; t++)
    {
      const bfd_target *p = bfd_target_vector[t];
      bfd *abfd = bfd_openw (dummy_name, p->name);
      int a;

      printf (_("%s\n (header %s, data %s)\n"), p->name,
	      endian_string (p->header_byteorder),
	      endian_string (p->byteorder));

      if (abfd == NULL)
	{
          bfd_nonfatal (dummy_name);
          ret = 0;
	  continue;
	}

      if (! bfd_set_format (abfd, bfd_object))
	{
	  if (bfd_get_error () != bfd_error_invalid_operation)
            {
	      bfd_nonfatal (p->name);
              ret = 0;
            }
	  bfd_close_all_done (abfd);
	  continue;
	}

      for (a = bfd_arch_obscure + 1; a < bfd_arch_last; a++)
	if (bfd_set_arch_mach (abfd, (enum bfd_architecture) a, 0))
	  printf ("  %s\n",
		  bfd_printable_arch_mach ((enum bfd_architecture) a, 0));
      bfd_close_all_done (abfd);
    }
  unlink (dummy_name);
  free (dummy_name);

  return ret;
}
