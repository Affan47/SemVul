unlock_pr (const DatabaseInfo database, const char *prID, ErrorDesc *err)
{
  char *lock_path;

  if (prID == NULL)
    return 0;

  lock_path = get_lock_path (database, prID);

  if (! fileExists (lock_path))
    {
      setError (err, CODE_PR_NOT_LOCKED, "PR %s is not locked.", prID);
      free (lock_path);
      return 0;
    }

  if (unlink (lock_path) != 0)
    {
      setError (err, CODE_FILE_ERROR, "Cannot delete lock file %s: %s.",
		lock_path, strerror (errno));
      free (lock_path);
      return 0;
    }

  free (lock_path);
  return 1;
}
