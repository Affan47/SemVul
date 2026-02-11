tag_function (const char *filename ATTRIBUTE_UNUSED,
	      unsigned tag ATTRIBUTE_UNUSED, unsigned length ATTRIBUTE_UNUSED)
{
  unsigned long pos = gcov_position ();

  printf (" ident=%u", gcov_read_unsigned ());
  printf (", checksum=0x%08x", gcov_read_unsigned ());

  if (gcov_position () - pos < length)
    {
      const char *name;

      name = gcov_read_string ();
      printf (", `%s'", name ? name : "NULL");
      name = gcov_read_string ();
      printf (" %s", name ? name : "NULL");
      printf (":%u", gcov_read_unsigned ());
    }
}
