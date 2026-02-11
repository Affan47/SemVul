c_pp_lookup_pragma (unsigned int id, const char **space, const char **name)
{
  const int n_omp_pragmas = sizeof (omp_pragmas) / sizeof (*omp_pragmas);
  int i;

  for (i = 0; i < n_omp_pragmas; ++i)
    if (omp_pragmas[i].id == id)
      {
	*space = "omp";
	*name = omp_pragmas[i].name;
	return;
      }

  if (id >= PRAGMA_FIRST_EXTERNAL
      && (id < PRAGMA_FIRST_EXTERNAL
	  + VEC_length (pragma_ns_name, registered_pp_pragmas)))
    {
      *space = VEC_index (pragma_ns_name, registered_pp_pragmas,
			  id - PRAGMA_FIRST_EXTERNAL)->space;
      *name = VEC_index (pragma_ns_name, registered_pp_pragmas,
			 id - PRAGMA_FIRST_EXTERNAL)->name;
      return;
    }

  gcc_unreachable ();
}
