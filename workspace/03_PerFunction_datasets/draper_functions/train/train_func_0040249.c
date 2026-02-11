tag_arcs (const char *filename ATTRIBUTE_UNUSED,
	  unsigned tag ATTRIBUTE_UNUSED, unsigned length ATTRIBUTE_UNUSED)
{
  unsigned n_arcs = GCOV_TAG_ARCS_NUM (length);

  printf (" %u arcs", n_arcs);
  if (flag_dump_contents)
    {
      unsigned ix;
      unsigned blockno = gcov_read_unsigned ();

      for (ix = 0; ix != n_arcs; ix++)
	{
	  unsigned dst, flags;

	  if (!(ix & 3))
	    {
	      printf ("\n");
	      print_prefix (filename, 0, gcov_position ());
	      printf ("\tblock %u:", blockno);
	    }
	  dst = gcov_read_unsigned ();
	  flags = gcov_read_unsigned ();
	  printf (" %u:%04x", dst, flags);
	}
    }
}
