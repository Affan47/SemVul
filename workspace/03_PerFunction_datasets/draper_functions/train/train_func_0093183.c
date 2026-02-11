read_debugging_info (bfd *abfd, asymbol **syms, long symcount, bfd_boolean no_messages)
{
  void *dhandle;
  bfd_boolean found;

  dhandle = debug_init ();
  if (dhandle == NULL)
    return NULL;

  if (! read_section_stabs_debugging_info (abfd, syms, symcount, dhandle,
					   &found))
    return NULL;

  if (bfd_get_flavour (abfd) == bfd_target_aout_flavour)
    {
      if (! read_symbol_stabs_debugging_info (abfd, syms, symcount, dhandle,
					      &found))
	return NULL;
    }

  if (bfd_get_flavour (abfd) == bfd_target_ieee_flavour)
    {
      if (! read_ieee_debugging_info (abfd, dhandle, &found))
	return NULL;
    }


  if (! found
      && bfd_get_flavour (abfd) == bfd_target_coff_flavour
      && symcount > 0)
    {
      if (! parse_coff (abfd, syms, symcount, dhandle))
	return NULL;
      found = TRUE;
    }

  if (! found)
    {
      if (! no_messages)
	non_fatal (_("%s: no recognized debugging information"),
		   bfd_get_filename (abfd));
      return NULL;
    }

  return dhandle;
}
