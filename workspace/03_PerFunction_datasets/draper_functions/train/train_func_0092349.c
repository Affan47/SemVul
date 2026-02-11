lang_relax_sections (bfd_boolean need_layout)
{
  if (RELAXATION_ENABLED)
    {

      int i = link_info.relax_pass;


      link_info.relax_pass = 0;

      while (i--)
	{

	  bfd_boolean relax_again;

	  link_info.relax_trip = -1;
	  do
	    {
	      link_info.relax_trip++;


	      lang_do_assignments (lang_assigning_phase_enum);


	      lang_reset_memory_regions ();


	      relax_again = FALSE;
	      lang_size_sections (&relax_again, FALSE);
	    }
	  while (relax_again);

	  link_info.relax_pass++;
	}
      need_layout = TRUE;
    }

  if (need_layout)
    {

      lang_do_assignments (lang_assigning_phase_enum);
      lang_reset_memory_regions ();
      lang_size_sections (NULL, TRUE);
    }
}
