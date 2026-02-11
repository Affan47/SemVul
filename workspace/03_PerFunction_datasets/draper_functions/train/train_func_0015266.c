should_hash(state *s, TCHAR *fn)
{
  int type = file_type(s,fn);

  if (NULL == s || NULL == fn)
    fatal_error("%s: Null state passed into should_hash", __progname);

  if (type == file_directory)
  {
    if (s->mode & mode_recursive)
      process_dir(s,fn);
    else
    {
      print_error_unicode(s,fn,"Is a directory");
    }
    return FALSE;
  }

#ifndef _WIN32
  if (type == file_symlink)
    return should_hash_symlink(s,fn,NULL);
#endif

  if (type == file_unknown)
    return FALSE;


  return TRUE;
}
