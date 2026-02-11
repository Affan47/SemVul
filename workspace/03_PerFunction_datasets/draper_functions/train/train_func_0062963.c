wd_sanity_check(const char *thing_to_stat,
		const char *progname,
		const char *what,
		dev_t old_dev,
		ino_t old_ino,
		struct stat *newinfo,
		int parent,
		int line_no,
		enum TraversalDirection direction,
		enum WdSanityCheckFatality isfatal,
		boolean *changed)
{
  const char *fstype;
  char *specific_what = NULL;
  int silent = 0;
  const char *current_dir = ".";

  *changed = false;

  set_stat_placeholders(newinfo);
  if ((*options.xstat) (current_dir, newinfo) != 0)
    fatal_file_error(thing_to_stat);

  if (old_dev != newinfo->st_dev)
    {
      *changed = true;
      specific_what = specific_dirname(what);
      fstype = filesystem_type(newinfo, current_dir);
      silent = fs_likely_to_be_automounted(fstype);


      if (TraversingDown == direction)
	{
#ifdef STAT_MOUNTPOINTS
	  isfatal = dirchange_is_fatal(specific_what,isfatal,silent,newinfo);
#else
	  isfatal = RETRY_IF_SANITY_CHECK_FAILS;
#endif
	}

      switch (isfatal)
	{
	case FATAL_IF_SANITY_CHECK_FAILS:
	  {
	    fstype = filesystem_type(newinfo, current_dir);
	    error (1, 0,
		   _("%s%s changed during execution of %s (old device number %ld, new device number %ld, file system type is %s) [ref %ld]"),
		   safely_quote_err_filename(0, specific_what),
		   parent ? "/.." : "",
		   safely_quote_err_filename(1, progname),
		   (long) old_dev,
		   (long) newinfo->st_dev,
		   fstype,
		   (long)line_no);

	    return false;
	  }

	case NON_FATAL_IF_SANITY_CHECK_FAILS:
	  {


	    free(specific_what);
	    return true;
	  }

	case RETRY_IF_SANITY_CHECK_FAILS:
	  return false;
	}
    }


  if (old_ino != newinfo->st_ino)
    {
      *changed = true;
      specific_what = specific_dirname(what);
      fstype = filesystem_type(newinfo, current_dir);

      error ((isfatal == FATAL_IF_SANITY_CHECK_FAILS) ? 1 : 0,
	     0,
	     _("%s%s changed during execution of %s "
	       "(old inode number %" PRIuMAX ", new inode number %" PRIuMAX
	       ", file system type is %s) [ref %ld]"),
	     safely_quote_err_filename(0, specific_what),
	     parent ? "/.." : "",
	     safely_quote_err_filename(1, progname),
	     (uintmax_t) old_ino,
	     (uintmax_t) newinfo->st_ino,
	     fstype,
	     (long)line_no);
      free(specific_what);
      return false;
    }

  return true;
}
