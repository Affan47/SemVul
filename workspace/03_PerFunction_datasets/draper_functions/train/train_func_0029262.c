cpp_write_pch_state (cpp_reader *r, FILE *f)
{
  struct macrodef_struct z;


  cpp_forall_identifiers (r, write_macdef, f);
  memset (&z, 0, sizeof (z));
  if (fwrite (&z, sizeof (z), 1, f) != 1)
    {
      cpp_errno (r, CPP_DL_ERROR, "while writing precompiled header");
      return -1;
    }

  if (!r->deps)
    r->deps = deps_init ();

  if (deps_save (r->deps, f) != 0)
    {
      cpp_errno (r, CPP_DL_ERROR, "while writing precompiled header");
      return -1;
    }

  return 0;
}
