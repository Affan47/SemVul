ldversion (int noisy)
{

  fprintf (stdout, _("GNU ld %s\n"), BFD_VERSION_STRING);

  if (noisy & 2)
    {
      printf (_("Copyright 2012 Free Software Foundation, Inc.\n"));
      printf (_("\
This program is free software; you may redistribute it under the terms of\n\
the GNU General Public License version 3 or (at your option) a later version.\n\
This program has absolutely no warranty.\n"));
    }

  if (noisy & 1)
    {
      ld_emulation_xfer_type **ptr = ld_emulations;

      printf (_("  Supported emulations:\n"));
      while (*ptr)
	{
	  printf ("   %s\n", (*ptr)->emulation_name);
	  ptr++;
	}
    }
}
