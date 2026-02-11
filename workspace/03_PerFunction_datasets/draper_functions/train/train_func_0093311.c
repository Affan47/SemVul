chdir_back (void)
{
  struct stat stat_buf;
  boolean dummy;

  if (starting_desc < 0)
    {
      if (options.debug_options & DebugSearch)
	fprintf(stderr, "chdir_back(): chdir(\"%s\")\n", starting_dir);

#ifdef STAT_MOUNTPOINTS


      if (NULL == mounted_devices)
	init_mounted_dev_list(1);
#endif

      if (chdir (starting_dir) != 0)
	fatal_file_error(starting_dir);

      wd_sanity_check(starting_dir,
		      program_name,
		      starting_dir,
		      starting_stat_buf.st_dev,
		      starting_stat_buf.st_ino,
		      &stat_buf, 0, __LINE__,
		      TraversingUp,
		      FATAL_IF_SANITY_CHECK_FAILS,
		      &dummy);
    }
  else
    {
      if (options.debug_options & DebugSearch)
	fprintf(stderr, "chdir_back(): chdir(<starting-point>)\n");

      if (fchdir (starting_desc) != 0)
	{
	  fatal_file_error(starting_dir);
	}
    }
}
