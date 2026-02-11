dump_decl_set (FILE *file, bitmap set)
{
  if (set)
    {
      bitmap_iterator bi;
      unsigned i;

      fprintf (file, "{ ");

      EXECUTE_IF_SET_IN_BITMAP (set, 0, i, bi)
	{
	  fprintf (file, "D.%u", i);
	  fprintf (file, " ");
	}

      fprintf (file, "}");
    }
  else
    fprintf (file, "NIL");
}
