free_dependency_caches (void)
{
  if (true_dependency_cache)
    {
      int i;

      for (i = 0; i < cache_size; i++)
	{
	  bitmap_clear (&true_dependency_cache[i]);
	  bitmap_clear (&anti_dependency_cache[i]);
	  bitmap_clear (&output_dependency_cache[i]);
#ifdef ENABLE_CHECKING
	  bitmap_clear (&forward_dependency_cache[i]);
#endif
	}
      free (true_dependency_cache);
      true_dependency_cache = NULL;
      free (anti_dependency_cache);
      anti_dependency_cache = NULL;
      free (output_dependency_cache);
      output_dependency_cache = NULL;
#ifdef ENABLE_CHECKING
      free (forward_dependency_cache);
      forward_dependency_cache = NULL;
#endif
    }
}
