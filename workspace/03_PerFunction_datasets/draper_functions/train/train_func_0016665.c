writeIndex (const DatabaseInfo database, ErrorDesc *err)
{
  FILE *fp;
  char *path, *workfile;
  PR *pr;
  IndexDesc indexDesc = getIndexDesc (database);
  struct stat buf;

  workfile = gnats_adm_dir (database, "indXXXXXX");
  fp = fopen_temporary_file (workfile, "w", 0644);
  if (fp == NULL)
    {
      setError (err, CODE_FILE_ERROR,
		"writeIndex () can't open the temporary file %s",
		workfile);
      free (workfile);
      return -1;
    }

  if (indexIsBinary (database))
    {
      unsigned char fieldCount = indexFieldCount (database);
      fwrite (&fieldCount, 1, 1, fp);
    }

  for (pr = getFirstPR (database, err); pr != NULL ; pr = getNextPR (pr))
    {
      size_t length;
      char *line = createIndexEntry (pr, &length);

      if (line != NULL)
	{
	  fwrite (line, 1, length, fp);
	  free (line);
	}
    }

  fclose (fp);

  block_signals ();

  path = gnats_adm_dir (database, indexDesc->path);


  if (stat (path, &buf) < 0)
    {


      if (errno != ENOENT)
	{
	  setError (err, CODE_FILE_ERROR,
		    "GNATS cannot stat the index: %s.", strerror (errno));
	  log_msg (LOG_ERR, 1, "error in writeIndex:",
		   getErrorMessage (*err));
	  return -1;
	}
    }

  if (buf.st_mtime > indexDesc->mtime)
    {
      setError (err, CODE_INVALID_INDEX,
		"Index has been modified since last read");
      log_msg (LOG_ERR, 1, "error in writeIndex:",
	       getErrorMessage (*err));

      punt (database, 0, "Attempting to write index file %s,\n\
but index has been modified since last read.  A PR has been modified,\n\
but the change has not been recorded in the index.  You must manually\n\
regenerate the index.", path);
      return -1;
    }

  if ((rename (workfile, path)) < 0)
    {
      if (errno != EXDEV)
	{
	  free (path);
	  setError (err, CODE_FILE_ERROR,
		    "could not rename temporary index %s into gnats-adm: %s",
		    workfile, strerror (errno));
	  return -1;
	}

      if (copy_file (workfile, path))
	{
	  setError (err, CODE_FILE_ERROR,
		   "could not copy temporary index %s into %s: %s",
		   workfile, path, strerror (errno));
	  return -1;
	}

      unlink (workfile);
    }

  free (path);
  free (workfile);
  unblock_signals ();
  return 0;
}
